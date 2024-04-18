/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filename_expand_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:31:14 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand_bonus.h"
#include "ms_exec_bonus.h"
#include <errno.h>
#include <sys/stat.h>

static t_bool	init(t_glob *glob, DIR **dir);
static t_bool	quit(char *next, DIR *dir);

t_bool	ms_expand_filename_expand(t_queue *queue, t_glob *glob)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*next;

	if (!init(glob, &dir))
		return (FALSE);
	while (dir)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (!ms_match(entry, glob))
			continue ;
		next = ms_join_path(glob, entry->d_name);
		if (!next)
			return (FALSE);
		if (!ms_enqueue(queue, next))
			return (quit(next, dir));
	}
	quit(NULL, dir);
	return (TRUE);
}

static t_bool	init(t_glob *glob, DIR **dir)
{
	struct stat	buf;

	if (*(glob->path) == '\0')
		*dir = opendir(".");
	else
	{
		if (stat(glob->path, &buf) == 0
			&& (S_IROTH & buf.st_mode) && s_isdir(buf.st_mode))
			*dir = opendir(glob->path);
		else
		{
			*dir = NULL;
			return (TRUE);
		}
	}
	if (*dir)
		return (TRUE);
	if (!*dir && errno == ENOENT)
		return (TRUE);
	return (FALSE);
}

static t_bool	quit(char *next, DIR *dir)
{
	if (next)
		free(next);
	if (dir)
		closedir(dir);
	return (FALSE);
}
