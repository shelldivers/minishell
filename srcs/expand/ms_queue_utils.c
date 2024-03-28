#include "libft.h"
#include "ms_expand.h"

void	ms_pick_queue(t_queue *queue, t_list *del)
{
	t_list	*node;

	if (queue->size == 0)
		return ;
	if (queue->size == 1)
	{
		free(del->content);
		free(del);
		queue->head = NULL;
		queue->tail = NULL;
		queue->size = 0;
		return ;
	}
	if (queue->head == del)
	{
		queue->head = del->next;
		free(del->content);
		free(del);
		queue->size--;
		return ;
	}
	node = queue->head;
	while (node->next != del)
		node = node->next;
	node->next = del->next;
	free(del->content);
	free(del);
	queue->size--;
}

t_queue	*ms_enqueue_arrays(t_queue *queue, char **arrays)
{
	size_t	i;

	i = 0;
	while (arrays[i])
	{
		if (!ms_enqueue(queue, arrays[i]))
			return (NULL);
		i++;
	}
	free(arrays);
	return (queue);
}

char	**ms_queue_to_arrays(t_queue *queue)
{
	char	**arrays;
	t_list	*node;
	size_t	i;

	arrays = (char **)malloc(sizeof(char *) * (queue->size + 1));
	if (!arrays)
		return (NULL);
	i = 0;
	node = queue->head;
	while (node)
	{
		arrays[i] = ft_strdup(node->content);
		if (!arrays[i])
		{
			while (i--)
				free(arrays[i]);
			free(arrays);
			return (NULL);
		}
		node = node->next;
		i++;
	}
	arrays[i] = NULL;
	return (arrays);
}
