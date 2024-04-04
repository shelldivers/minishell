/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filename.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/04 20:02:45 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"
#include <fcntl.h>
#include <unistd.h>

static t_bool	init(t_queue **queue, int *depth, char *str);
static int		get_depth(char *str);
static void		ms_mark_asterisk(char *str);

char	**ms_expand_filename(char *str)
{
	t_queue	*queue;
	int		depth;

	if (!init(&queue, &depth, str))
		return (NULL);
	if (depth < 0)
		return (ms_inspect_filename(queue, 1, str));
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

static void	ms_mark_asterisk(char *str)
{
	t_bool	quote;
	t_bool	dquote;

	quote = FALSE;
	dquote = FALSE;
	while (*str)
	{
		if (!quote && *str == '\"')
		{
			dquote = (t_bool) !dquote;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
			continue ;
		}
		else if (!dquote && *str == '\'')
		{
			quote = (t_bool) !quote;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
			continue ;
		}
		else if (!quote && !dquote && *str == '*')
			*str = ASTERISK;
		str++;
	}
}

static int	get_depth(char *str)
{
	int		max_depth;
	t_bool	path;

	if (*str == '\0')
		return (0);
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
	if (path && *(str - 1) == '/')
		max_depth--;
	return (max_depth);
}

static t_bool	init(t_queue **queue, int *depth, char *str)
{
	char	*tmp;

	*queue = ms_init_queue();
	if (!*queue)
		return (FALSE);
	tmp = ft_strdup(str);
	if (!tmp)
	{
		ms_destroy_queue(*queue, free);
		return (FALSE);
	}
	ms_mark_asterisk(tmp);
	*depth = get_depth(tmp);
	ms_enqueue(*queue, tmp);
	return (TRUE);
}
