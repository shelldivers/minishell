#include "minishell.h"
#include <stdlib.h>

/**
 * @notice You must free head node after calling this function
 */
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
