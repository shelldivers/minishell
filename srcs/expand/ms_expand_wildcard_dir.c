/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_wildcard_dir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:59 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/07 10:49:12 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"
#include <dirent.h>
#include <stdlib.h>

/**
 * @errno ENOMEM
 */
t_list	**ms_wildcard_extend(DIR *dir, char *path, char *str)
{
	t_wildcard		wc;
	t_list			**lst;

	wc.prefix = ms_wildcard_get_prefix(str);
	if (!wc.prefix)
		return (NULL);
	wc.suffix = ms_wildcard_get_suffix(str);
	if (!wc.suffix)
	{
		free(wc.prefix);
		return (NULL);
	}
	wc.last = ms_wildcard_get_last(str);
	if (!wc.last)
	{
		free(wc.prefix);
		free(wc.suffix);
		return (NULL);
	}
	lst = ms_wildcard_d_loop(dir, path, &wc);
	free(wc.prefix);
	free(wc.suffix);
	free(wc.last);
	return (lst);
}

/**
 * @errno ENOMEM
 */
t_list	**ms_wildcard_d_loop(DIR *dir, char *path, t_wildcard *wc)
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
		if (!ms_wildcard_is_type(*(entry->d_name), entry->d_type, wc)
			|| !ms_wildcard_is_match(entry->d_name, wc))
			continue ;
		if (!ms_wildcard_add(lst, entry->d_name, path, wc->last))
		{
			ft_lstclear(lst, free);
			free(lst);
			return (NULL);
		}
	}
	return (lst);
}

t_bool	ms_wildcard_is_type(char hidden, int type, t_wildcard *wc)
{
	t_bool	is_dir;
	t_bool	is_hidden;

	is_dir = FALSE;
	if (ft_strchr(wc->last, '/') != NULL)
		is_dir = TRUE;
	if (is_dir && type != DT_DIR)
		return (FALSE);
	is_hidden = FALSE;
	if (wc->prefix[0] == '.')
		is_hidden = TRUE;
	if ((is_hidden && hidden != '.')
		|| (!is_hidden && hidden == '.'))
		return (FALSE);
	return (TRUE);
}

t_bool	ms_wildcard_is_match(char *name, t_wildcard *wc)
{
	size_t	prefix_len;
	size_t	suffix_len;
	size_t	name_len;

	prefix_len = ft_strlen(wc->prefix);
	suffix_len = ft_strlen(wc->suffix);
	name_len = ft_strlen(name);
	if (ft_strncmp(name, wc->prefix, prefix_len) != 0)
		return (FALSE);
	if (ft_strncmp(name + name_len - suffix_len, wc->suffix, suffix_len) != 0)
		return (FALSE);
	return (TRUE);
}

/**
 * @errno ENOMEM
 */
t_bool	ms_wildcard_add(t_list **head, char *d_name, char *path, char *last)
{
	char	*name;
	t_list	*node;

	name = ms_wildcard_combine(d_name, path, last);
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
