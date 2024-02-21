#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

t_env	*ms_env_push_back(t_env **head, t_env *env)
{
	t_env	*node;

	if (!head || !env)
		return (NULL);
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

void	ms_env_clear(t_env **head)
{
	t_env	*node;
	t_env	*next;

	if (!head || !*head)
		return ;
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

	if (!head)
		return (0);
	node = head;
	size = 0;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
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
		return (FALSE);
	head = (t_env **)malloc(sizeof(t_env *));
	*head = NULL;
	while (*envp++)
	{
		env = ms_str_to_env(*envp);
		if (!env)
		{
			ms_env_clear(head);
			free(head);
			return (FALSE);
		}
		ms_env_push_back(head, env);
		envp++;
	}
	return (head);
}
