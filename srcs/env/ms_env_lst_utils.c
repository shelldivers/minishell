/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:29:47 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/04 19:29:51 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/errno.h>

/**
 * @notice You must free head node after calling this function
 */
void	ms_env_clear(t_env **head)
{
	t_env	*node;
	t_env	*next;

	node = *head;
	while (node)
	{
		next = node->next;
		free(node->key);
		free(node->value);
		free(node);
		node = next;
	}
	*head = NULL;
}

size_t	ms_env_size(t_env *head)
{
	t_env	*node;
	size_t	size;

	node = head;
	size = 0;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}

t_env	*ms_env_push_back(t_env **head, t_env *env)
{
	t_env	*node;

	if (*head == NULL)
		*head = env;
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = env;
	}
	return (env);
}

void	ms_env_print_all(t_env *env)
{
	while (env)
	{
		printf("%s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

/**
 * @errno EINVAL
 */
t_bool	ms_is_valid_env_key(char *key)
{
	if (!ft_isalpha(*key) && *key != '_')
	{
		errno = EINVAL;
		return (FALSE);
	}
	key++;
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
		{
			errno = EINVAL;
			return (FALSE);
		}
		key++;
	}
	return (TRUE);
}
