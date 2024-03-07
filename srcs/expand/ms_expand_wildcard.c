/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:55 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/07 10:49:13 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_env.h"
#include "ms_expand.h"
#include <dirent.h>
#include <stdlib.h>

t_bool	ms_expand_wildcard(t_list **head, t_list **nod, t_env **env, int depth)
{
	t_list	**extend;

	extend = ms_wildcard_loop(nod, env, depth);
	if (!extend)
		return (FALSE);
	if (!*extend || ft_strchr((*extend)->content, '*') != NULL)
	{
		ft_lstclear(extend, free);
		free(extend);
		if (depth == 0)
			*nod = (*nod)->next;
		else
			*nod = ms_wildcard_remove(head, nod);
		return (TRUE);
	}
	*nod = ms_wildcard_replace(head, nod, extend);
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
t_list	**ms_wildcard_loop(t_list **node, t_env **env, int depth)
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
	if (!ms_expand_proceed(extend, env, depth + 1))
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
	t_list	*tmp;

	prev = *head;
	if (prev == *node)
		*head = *extend;
	else
	{
		while (prev->next != *node)
			prev = prev->next;
		prev->next = *extend;
	}
	next = (*node)->next;
	tmp = *extend;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = next;
	free((*node)->content);
	free(*node);
	return (next);
}

t_list	*ms_wildcard_remove(t_list **head, t_list **remove)
{
	t_list	*prev;
	t_list	*next;

	prev = *head;
	if (prev == *remove)
		*head = (*remove)->next;
	else
	{
		while (prev->next != *remove)
			prev = prev->next;
	}
	next = (*remove)->next;
	prev->next = next;
	free((*remove)->content);
	free(*remove);
	return (next);
}
