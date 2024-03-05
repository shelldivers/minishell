/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_serialize_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:28:07 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/04 19:28:10 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "libft.h"
#include <stdlib.h>

static t_bool	ms_str_assign_env(t_env *env, char *str, char *sep);
static t_bool	ms_str_assign_empty_env(t_env *env, char *str);

/**
 * @errno ENOMEM
 */
t_bool	ms_env_move(char **envp, t_env **env, size_t start)
{
	char	**tmp;
	size_t	tmp_size;
	size_t	i;

	tmp = ms_env_serialize(*env);
	if (!tmp)
		return (FALSE);
	tmp_size = ms_env_size(*env);
	i = 0;
	while (i < tmp_size)
	{
		envp[start + i] = tmp[i];
		i++;
	}
	envp[start + tmp_size] = NULL;
	free(tmp);
	return (TRUE);
}

/**
 * @errno ENOMEM
 */
char	*ms_env_to_str(t_env *env)
{
	char	*str;
	size_t	key_length;
	size_t	val_length;

	key_length = ft_strlen(env->key);
	val_length = ft_strlen(env->value);
	str = (char *)malloc(sizeof(char) * (key_length + val_length + 2));
	if (!str)
		return (NULL);
	ft_memcpy(str, env->key, key_length);
	str[key_length] = '=';
	ft_memcpy(str + key_length + 1, env->value, val_length + 1);
	return (str);
}

/**
 * @errno ENOMEM
 */
t_env	*ms_str_to_env(char *str)
{
	t_env	*env;
	char	*sep;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (FALSE);
	sep = ft_strchr(str, '=');
	if (!ms_str_assign_env(env, str, sep))
	{
		free(env);
		return (NULL);
	}
	return (env);
}

/**
 * @errno ENOMEM
 */
static t_bool	ms_str_assign_env(t_env *env, char *str, char *sep)
{
	if (!sep)
	{
		if (!ms_str_assign_empty_env(env, str))
			return (FALSE);
	}
	else
	{
		env->key = ft_strndup(str, sep - str);
		if (!env->key)
			return (FALSE);
		env->value = ft_strdup(sep + 1);
		if (!env->value)
		{
			free(env->key);
			return (FALSE);
		}
		env->next = NULL;
	}
	return (TRUE);
}

/**
 * @errno ENOMEM
 */
static t_bool	ms_str_assign_empty_env(t_env *env, char *str)
{
	env->key = ft_strdup(str);
	if (!env->key)
		return (FALSE);
	env->value = ft_strdup("");
	if (!env->value)
	{
		free(env->key);
		return (FALSE);
	}
	env->next = NULL;
	return (TRUE);
}
