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
