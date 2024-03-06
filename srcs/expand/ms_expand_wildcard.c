#include "libft.h"
#include "ft_printf.h"
#include "ms_expand.h"
#include "ms_env.h"
#include <dirent.h>
#include <stdlib.h>

/**
 * @errno ENOMEM
 */
t_bool	ms_wildcard_add(t_list **head, char *d_name, char *path, char *suffix)
{
	char	*name;
	t_list	*node;

	name = ms_wildcard_combine(d_name, path, suffix);
	if (!name)
		return (FALSE);
	node = ft_lstnew(name);
	if (!node)
	{
		free(name);
		return (FALSE);
	}
	ft_lstadd_back(head, node);
	return (TRUE);
}

/**
 * @errno ENOMEM
 */
t_list	**ms_wildcard_d_loop(DIR *dir, char *path, char *prefix, char *suffix)
{
	struct dirent	*entry;
	t_list			**lst;

	lst = (t_list **)malloc(sizeof(t_list *));
	if (!lst)
		return (NULL);
	*lst = NULL;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (!ms_wildcard_is_match(entry->d_name, entry->d_type, prefix, suffix))
			continue ;
		if (!ms_wildcard_add(lst, entry->d_name, path, suffix))
		{
			ft_lstclear(lst, free);
			free(lst);
			return (NULL);
		}
	}
	return (lst);
}

/**
 * @errno ENOMEM
 */
t_list	**ms_wildcard_extend(DIR *dir, char *path, char *str)
{
	char			*prefix;
	char			*suffix;
	t_list			**lst;

	prefix = ms_wildcard_get_prefix(str);
	if (!prefix)
		return (NULL);
	suffix = ms_wildcard_get_suffix(str);
	if (!suffix)
	{
		free(prefix);
		return (NULL);
	}
	lst = ms_wildcard_d_loop(dir, path, prefix, suffix);
	free(prefix);
	free(suffix);
	return (lst);
}

t_list	*ms_wildcard_replace(t_list **head, t_list **node, t_list **extend)
{
	t_list	*prev;
	t_list	*next;
	t_list	*next_tmp;

	next_tmp = (*node)->next;
	prev = *head;
	if (prev == *node)
	{
		if (*extend == NULL)
			*head = (*node)->next;
		else
		{
			*head = *extend;
			next = *extend;
			while (next->next)
				next = next->next;
			next->next = next_tmp;
		}
		free((*node)->content);
		free(*node);
		return (next_tmp);
	}
	else
	{
		while (prev->next != *node)
			prev = prev->next;
		if (*extend == NULL)
			prev->next = (*node)->next;
		else
		{
			prev->next = *extend;
			next = *extend;
			while (next->next)
				next = next->next;
			next->next = next_tmp;
		}
		free((*node)->content);
		free(*node);
		return (next_tmp);
	}
}

/**
 * @errno EACCES
 * @errno EBADF
 * @errno EMFILE
 * @errno ENFILE
 * @errno ENOENT
 * @errno ENOMEM
 * @errno ENOTDIR
 */
t_list	**ms_expand_wildcard(t_list **node, t_env **env)
{
	char			*path;
	t_list			**extend;
	DIR				*dir;

	path = ms_wildcard_get_path((*node)->content);
	if (!path)
		return (NULL);
	dir = opendir(path);
	if (!dir)
	{
		free(path);
		return (NULL);
	}
	extend = ms_wildcard_extend(dir, path, (*node)->content);
	free(path);
	closedir(dir);
	if (!extend)
		return (NULL);
	if (!ms_expand_proceed(extend, env))
	{
		free(extend);
		return (NULL);
	}
	return (extend);
}
