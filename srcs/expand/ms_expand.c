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

static void		*ms_expand_dispatcher(char c);

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
	if (!ms_expand_proceed(head, env, 0))
	{
		free(head);
		return (NULL);
	}
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
			ft_lstclear(head, free);
			return (FALSE);
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
		f = ms_expand_dispatcher(((char *)(*node)->content)[i]);
		if (f != NULL && f != WILDCARD)
		{
			if (!((t_bool(*)(t_list **, t_list **, int *, t_env **))f)
					(head, node, &i, env))
				return (FALSE);
		}
		else if (f == WILDCARD)
		{
			result = ms_expand_wildcard(head, node, env, depth);
			if (result == ERROR)
				return (FALSE);
			else if (result == MATCH)
				return (TRUE);
		}
		i++;
	}
	*node = (*node)->next;
	return (TRUE);
}

static void	*ms_expand_dispatcher(char c)
{
	if (c == '\'')
		return (ms_expand_quote);
	else if (c == '\"')
		return (ms_expand_dquote);
	else if (c == '\\')
		return (ms_expand_escape);
	else if (c == '$')
		return (ms_expand_env);
	else if (c == '*')
		return (WILDCARD);
	else
		return (NULL);
}
