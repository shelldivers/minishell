#include "ms_expand.h"
#include "ms_env.h"
#include <dirent.h>
#include <stdlib.h>

static t_bool	ms_wildcard_is_valid(t_list *node);


t_bool	ms_expand_wildcard(t_list **head, t_list **node, t_env **env)
{
	t_list	**extend;

	extend = ms_wildcard_loop(node, env);
	if (!extend)
		return (FALSE);
	if (!ms_wildcard_is_valid(*extend))
	{
		ft_lstclear(extend, free);
		free(extend);
		*node = (*node)->next;
		return (TRUE);
	}
	*node = ms_wildcard_replace(head, node, extend);
	free(extend);
	return (TRUE);
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
t_list	**ms_wildcard_loop(t_list **node, t_env **env)
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

static t_bool	ms_wildcard_is_valid(t_list *node)
{
	if (!node)
		return (FALSE);
	if (ft_strchr(node->content, '*') != NULL)
		return (FALSE);
	return (TRUE);
}
