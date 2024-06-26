/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filename_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/08 15:12:33 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"
#include <fcntl.h>
#include <unistd.h>

static char		**no_match(t_queue *queue, const char *str);
static char		**match(t_queue *queue);
static t_bool	is_exist(char *str);

char	**ms_inspect_filename(t_queue *queue, int depth, char *str)
{
	if (depth > 0 || queue->size == 0)
		return (no_match(queue, str));
	return (match(queue));
}

static char	**no_match(t_queue *queue, const char *str)
{
	char	**result;

	ms_destroy_queue(queue, free);
	result = (char **)malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(str);
	if (!result[0])
	{
		free(result);
		return (NULL);
	}
	result[1] = NULL;
	return (result);
}

static char	**match(t_queue *queue)
{
	char	**result;
	t_list	*node;
	t_list	*tmp;

	node = queue->head;
	while (node)
	{
		tmp = node->next;
		if (!is_exist(node->content))
			ms_queue_remove(queue, node, free);
		node = tmp;
	}
	result = ms_queue_to_array_dequote(queue);
	ms_destroy_queue(queue, free);
	return (result);
}

static t_bool	is_exist(char *str)
{
	if (access(str, F_OK) == 0)
		return (TRUE);
	return (FALSE);
}
