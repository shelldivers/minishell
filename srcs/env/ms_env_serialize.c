/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_serialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:28:05 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/04 19:28:11 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include <stdlib.h>

/**
 * @errno ENOMEM
 */
char	**ms_env_serialize(t_env *env)
{
	char	**envp;
	size_t	i;

	envp = (char **)malloc(sizeof(char *) * (ms_env_size(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = ms_env_to_str(env);
		if (!envp[i])
		{
			while (i--)
				free(envp[i]);
			free(envp);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

/**
 * @errno ENOMEM
 */
t_env	**ms_env_deserialize(char **envp)
{
	t_env	**head;
	t_env	*env;

	head = (t_env **)malloc(sizeof(t_env *));
	if (!head)
		return (NULL);
	*head = NULL;
	while (*envp)
	{
		env = ms_str_to_env(*envp);
		if (!env)
		{
			ms_env_clear(head);
			free(head);
			return (NULL);
		}
		ms_env_push_back(head, env);
		envp++;
	}
	return (head);
}

/**
 * @errno ENOMEM
 */
char	**ms_env_serialize_union(t_env **env1, t_env **env2)
{
	char	**envp;
	size_t	env1_size;
	size_t	env2_size;

	env1_size = ms_env_size(*env1);
	env2_size = ms_env_size(*env2);
	envp = (char **)malloc(sizeof(char *) * (env1_size + env2_size + 1));
	if (!envp)
		return (NULL);
	envp[env1_size + env2_size] = NULL;
	if (!ms_env_move(envp, env1, 0))
	{
		free(envp);
		return (NULL);
	}
	if (!ms_env_move(envp, env2, env1_size))
	{
		while (env1_size--)
			free(envp[env1_size]);
		free(envp);
		return (NULL);
	}
	return (envp);
}
