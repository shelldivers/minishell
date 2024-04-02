/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filename.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/02 17:13:11 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"
#include <fcntl.h>
#include <unistd.h>

static int		get_depth(char *str);
static t_bool	is_exist(char *str);
static char		**no_match(const char *str);
static char		**match(t_queue *queue);

char	**ms_expand_filename(char *str)
{
	t_queue	*queue;
	int		depth;

	queue = ms_init_queue();
	if (!queue)
		return (NULL);
	depth = get_depth(str);
	ms_enqueue(queue, str);
	while (1)
	{
		if (queue->size <= 0 || depth-- <= 0)
			break ;
		if (!ms_expand_filename_search(queue, queue->size))
		{
			ms_destroy_queue(queue, free);
			return (NULL);
		}
	}
	if (depth > 0 || queue->size == 0)
		return (no_match(str));
	return (match(queue));
}

static int	get_depth(char *str)
{
	int		max_depth;
	t_bool	path;

	path = TRUE;
	max_depth = 0;
	while (*str)
	{
		if (*str == '/')
			path = TRUE;
		else if (path && *str == ASTERISK)
		{
			path = FALSE;
			max_depth++;
		}
		str++;
	}
	return (max_depth);
}

static char	**no_match(const char *str)
{
	char	**result;

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
	result = ms_queue_to_array(queue);
	ms_destroy_queue(queue, free);
	return (result);
}

static t_bool	is_exist(char *str)
{
	DIR		*dir;
	int		fd;
	t_bool	result;

	dir = opendir(str);
	fd = open(str, O_RDONLY);
	result = FALSE;
	if (dir || fd >= 0)
		result = TRUE;
	if (fd >= 0)
		close(fd);
	if (dir)
		closedir(dir);
	return (result);
}
