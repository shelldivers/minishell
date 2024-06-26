/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:29:50 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/04 19:29:50 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "libft.h"
#include <stdlib.h>

static t_bool	ms_swap_env(t_env *env, char *value);
static t_env	*ms_assign_env(char *key, char *value);

void	ms_env_remove(t_env **head, char *key)
{
	t_env	*env;
	t_env	*prev;

	env = *head;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (!prev)
				*head = env->next;
			else
				prev->next = env->next;
			free(env->key);
			free(env->value);
			free(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

char	*ms_getenv(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_bool	ms_setenv(t_env **head, char *key, char *value)
{
	t_env	*env;

	if (!ms_is_valid_env_key(key))
		return (FALSE);
	env = *head;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (!ms_swap_env(env, value))
				return (FALSE);
			return (TRUE);
		}
		env = env->next;
	}
	env = ms_assign_env(key, value);
	if (!env)
		return (FALSE);
	ms_env_push_back(head, env);
	return (TRUE);
}

static t_bool	ms_swap_env(t_env *env, char *value)
{
	char	*tmp;

	tmp = ft_strdup(value);
	if (!tmp)
		return (FALSE);
	free(env->value);
	env->value = tmp;
	return (TRUE);
}

static t_env	*ms_assign_env(char *key, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (FALSE);
	env->key = ft_strdup(key);
	if (!env->key)
	{
		free(env);
		return (FALSE);
	}
	env->value = ft_strdup(value);
	if (!env->value)
	{
		free(env->key);
		free(env);
		return (FALSE);
	}
	env->next = NULL;
	return (env);
}
