/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/07 10:49:14 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"
#include "ms_error.h"

char	**ms_expand(char **argv, t_env **env)
{
	t_list	**head;
	char	**new_argv;

	head = ms_expand_init(argv);
	if (!head)
	{
		ms_puterror_arg(*env, *argv);
		return (NULL);
	}
	ms_expand_proceed(head, env, 0);
	new_argv = ms_expand_transform_free(head);
	if (!new_argv)
	{
		ms_puterror_arg(*env, *argv);
		ft_lstclear(head, free);
		free(head);
		return (NULL);
	}
	return (new_argv);
}

t_bool	ms_expand_proceed(t_list **head, t_env **env, int depth)
{
	t_list	*node;

	node = *head;
	while (node)
	{
		if (!ms_expand_handler(head, &node, env, depth))
		{
			ms_puterror_arg(*env, node->content);
			node = ms_wildcard_remove(head, &node);
		}
	}
	return (TRUE);
}

/**
 * @errno ENOMEM
 */
t_bool	ms_expand_handler(t_list **head, t_list **node, t_env **env, int depth)
{
	int		i;
	void	*f;
	int		result;

	i = 0;
	while (*node && ((char *)(*node)->content)[i] && i != -1)
	{
		if (((char *)(*node)->content)[i] == '*')
		{
			result = ms_expand_wildcard(head, node, env, depth);
			if (result == ERROR)
				return (FALSE);
			else if (result == MATCH)
				return (TRUE);
			i++;
		}
		else
		{
			if (!ms_expand_route(head, node, &i, env))
				return (FALSE);
		}
	}
	*node = (*node)->next;
	return (TRUE);
}

t_bool	ms_expand_route(t_list **lst, t_list **node, int *idx, t_env **env)
{
	char	c;

	c = ((char *)(*node)->content)[*idx];
	if (c == '\'')
		return (ms_expand_quote(node, idx));
	else if (c == '\"')
		return (ms_expand_dquote(node, idx, env));
	else if (c == '\\')
		return (ms_expand_escape(node, idx));
	else if (c == '$')
		return (ms_expand_env(node, idx, env));
	else
	{
		*idx += 1;
		return (TRUE);
	}
}
