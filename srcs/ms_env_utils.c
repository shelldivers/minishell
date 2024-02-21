#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static t_bool	ms_str_assign_env(t_env *env, char *str, char *sep);

t_env	*ms_str_to_env(char *str)
{
	t_env	*env;
	char	*sep;

	if (!str)
		return (NULL);
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)	// todo : malloc error
		return (NULL);
	sep = ft_strchr(str, '=');
	if (!sep)	// todo : invalid env format
	{
		free(env);
		return (NULL);
	}
	if (!ms_str_assign_env(env, str, sep))
	{
		free(env);
		return (NULL);
	}
	return (env);
}

char	*ms_env_to_str(t_env *env)
{
	char	*str;
	size_t	key_length;
	size_t	val_length;

	if (!env)
		return (NULL);
	key_length = ft_strlen(env->key);
	val_length = ft_strlen(env->value);
	str = (char *)malloc(sizeof(char) * (key_length + val_length + 2));
	if (!str)	// todo : malloc error
		return (NULL);
	ft_memcpy(str, env->key, key_length);
	str[key_length] = '=';
	ft_memcpy(str + key_length + 1, env->value, val_length + 1);
	return (str);
}

static t_bool	ms_str_assign_env(t_env *env, char *str, char *sep)
{
	env->key = ft_strndup(str, sep - str);
	if (!env->key)	// todo : malloc error
		return (FALSE);
	env->value = ft_strdup(sep + 1);
	if (!env->value)	// todo : malloc error
	{
		free(env->key);
		return (FALSE);
	}
	env->next = NULL;
	return (TRUE);
}
