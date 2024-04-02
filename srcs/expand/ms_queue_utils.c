/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_queue_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:13:02 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/02 18:40:45 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"

void	ms_queue_remove(t_queue *queue, t_list *target, void *del)
{
	t_list	*node;

	if (queue->size == 0)
		return ;
	if (queue->size == 1)
	{
		queue->head = NULL;
		queue->tail = NULL;
	}
	else if (queue->head == target)
		queue->head = target->next;
	else
	{
		node = queue->head;
		while (node->next != target)
			node = node->next;
		node->next = target->next;
	}
	ft_lstdelone(target, del);
	queue->size--;
}

t_bool	ms_enqueue_array(t_queue *queue, char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		if (!ms_enqueue(queue, array[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	**ms_queue_to_array(t_queue *queue)
{
	char	**array;
	t_list	*node;
	size_t	i;

	array = (char **)malloc(sizeof(char *) * (queue->size + 1));
	if (!array)
		return (NULL);
	i = 0;
	node = queue->head;
	while (node)
	{
		array[i] = ft_strdup(node->content);
		if (!array[i])
		{
			while (i--)
				free(array[i]);
			free(array);
			return (NULL);
		}
		node = node->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
