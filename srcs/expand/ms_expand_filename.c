/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filename.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/02 18:40:57 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"
#include <fcntl.h>
#include <unistd.h>

static t_bool	init(t_queue **queue, int *depth, char *str);
static int		get_depth(char *str);
static t_bool	is_exist(char *str);

char	**ms_expand_filename(char *str)
{
	t_queue	*queue;
	int		depth;

	if (!init(&queue, &depth, str))
		return (NULL);
	while (1)
	{
		if (queue->size <= 0 || depth-- < 0)
			break ;
		if (!ms_expand_filename_search(queue, queue->size))
		{
			ms_destroy_queue(queue, free);
			return (NULL);
		}
	}
	return (ms_inspect_filename(queue, depth, str));
}

static t_bool	init(t_queue **queue, int *depth, char *str)
{
	char	*tmp;

	*queue = ms_init_queue();
	if (!*queue)
		return (FALSE);
	*depth = get_depth(str);
	tmp = ft_strdup(str);
	if (!tmp)
	{
		ms_destroy_queue(*queue, free);
		return (FALSE);
	}
	ms_enqueue(*queue, tmp);
	return (TRUE);
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
