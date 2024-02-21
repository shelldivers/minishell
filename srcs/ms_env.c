#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static t_env	*ms_assign_env(char *key, char *value);

t_bool	ms_setenv(t_env **head, char *key, char *value)
{
	t_env	*env;
	char	*tmp;

	if (!head || !key || !value)
		return (FALSE);
	env = *head;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			tmp = ft_strdup(value);
			if (!tmp)
				return (FALSE);
			free(env->value);
			env->value = tmp;
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

char	*ms_getenv(t_env *env, char *key)
{
	if (!env || !key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**ms_env_serialize(t_env *env)
{
	char	**envp;
	size_t	i;

	if (!env)
		return (NULL);
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

	if (!envp)
		return (NULL);
	head = (t_env **)malloc(sizeof(t_env *));
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
