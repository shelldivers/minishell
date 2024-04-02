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

static t_bool	init(t_glob *glob, DIR **dir);
static t_bool	quit(char *path, DIR *dir);

t_bool	ms_expand_filename_expand(t_queue *queue, t_glob *glob)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*path;

	if (!init(glob, &dir))
		return (FALSE);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (!ms_match(entry, glob))
			continue ;
		path = ms_join_path(glob, entry->d_name);
		if (!path)
			return (FALSE);
		if (!ms_enqueue(queue, path))
			return (quit(path, dir));
	}
	closedir(dir);
	return (TRUE);
}

static t_bool	init(t_glob *glob, DIR **dir)
{
	if (*(glob->path) == '\0')
		*dir = opendir(".");
	else
		*dir = opendir(glob->path);
	if (!*dir)
		return (FALSE);
	return (TRUE);
}

static t_bool	quit(char *path, DIR *dir)
{
	free(path);
	closedir(dir);
	return (FALSE);
}
