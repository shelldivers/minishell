/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filename_expand.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/02 17:13:12 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"
#include <errno.h>

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
	if (*(glob->path) == '\0')
		*dir = opendir(".");
	else
		*dir = opendir(glob->path);
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
