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

t_bool	ms_wildcard_is_match(char *name, int type, char *prefix, char *suffix)
{
	t_bool	is_dir;
	t_bool	is_hidden;

	is_dir = FALSE;
	if (ft_strchr(suffix, '/') != NULL)
		is_dir = TRUE;
	if (is_dir && type != DT_DIR)
		return (FALSE);
	is_hidden = FALSE;
	if (prefix[0] == '.')
		is_hidden = TRUE;
	if ((is_hidden && name[0] != '.')
		|| (!is_hidden && name[0] == '.'))
		return (FALSE);
	if (ft_strncmp(name, prefix, ft_strlen(prefix)) != 0)
		return (FALSE);
	return (TRUE);
}

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
