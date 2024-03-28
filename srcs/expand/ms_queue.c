#include "ms_expand.h"

t_queue	*ms_init_queue(void)
{
	t_queue	*queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	if (!queue)
		return (NULL);
	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;
	return (queue);
}

void	ms_destroy_queue(t_queue *queue)
{
	t_list	*node;

	while (queue->size > 0)
	{
		node = ms_dequeue(queue);
		free(node->content);
		free(node);
	}
	free(queue);
}

t_bool	ms_enqueue(t_queue *queue, char *str)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (FALSE);
	node->content = str;
	node->next = NULL;
	if (queue->size == 0)
	{
		queue->head = node;
		queue->tail = node;
	}
	else
	{
		queue->tail->next = node;
		queue->tail = node;
	}
	queue->size++;
	return (TRUE);
}

t_list	*ms_dequeue(t_queue *queue)
{
	t_list	*node;

	if (queue->size == 0)
		return (NULL);
	node = queue->head;
	queue->head = queue->head->next;
	queue->size--;
	return (node);
}

void	ms_clear_queue(t_queue *queue)
{
	t_list	*node;

	while (queue->size > 0)
	{
		node = ms_dequeue(queue);
		free(node->content);
		free(node);
	}
}
