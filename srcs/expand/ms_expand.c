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

char	**ms_expand(char **argv, t_env **env, int *exit_code)
{
	t_list	**head;
	char	**new_argv;

	head = ms_expand_init(argv);
	if (!head)
	{
		ms_puterror_arg(*env, *argv);
		return (NULL);
	}
	ms_expand_proceed(head, env, (t_exp){0, exit_code});
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

t_bool	ms_expand_proceed(t_list **head, t_env **env, t_exp exp)
{
	t_list	*node;

	node = *head;
	while (node)
	{
		if (!ms_expand_handler(head, &node, env, exp))
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
t_bool	ms_expand_handler(t_list **head, t_list **node, t_env **env, t_exp exp)
{
	int		i;
	int		result;

	i = 0;
	while (*node && ((char *)(*node)->content)[i] && i != -1)
	{
		if (((char *)(*node)->content)[i] != '*')
		{
			if (!ms_expand_route(node, &i, env, exp))
				return (FALSE);
		}
		else
		{
			result = ms_expand_wildcard(head, node, env, exp);
			if (result == ERROR)
				return (FALSE);
			else if (result == MATCH)
				return (TRUE);
			i++;
		}
	}
	*node = (*node)->next;
	return (TRUE);
}

t_bool	ms_expand_route(t_list **node, int *idx, t_env **env, t_exp exp)
{
	char	c;

	c = ((char *)(*node)->content)[*idx];
	if (c == '\'')
		return (ms_expand_quote(node, idx));
	else if (c == '\"')
		return (ms_expand_dquote(node, idx, env, exp));
	else if (c == '\\')
		return (ms_expand_escape(node, idx));
	else if (c == '$')
		return (ms_expand_env(node, idx, env, exp.exit_code));
	else
	{
		*idx += 1;
		return (TRUE);
	}
}
