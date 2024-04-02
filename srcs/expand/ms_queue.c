/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:13:04 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/02 18:40:39 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

void	ms_destroy_queue(t_queue *queue, void *del)
{
	t_list	*node;

	while (queue->size > 0)
	{
		node = ms_dequeue(queue);
		ft_lstdelone(node, del);
	}
	free(queue);
}

t_bool	ms_enqueue(t_queue *queue, void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (FALSE);
	node->content = content;
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

void	ms_clear_queue(t_queue *queue, void *del)
{
	t_list	*node;

	while (queue->size > 0)
	{
		node = ms_dequeue(queue);
		ft_lstdelone(node, del);
	}
}
