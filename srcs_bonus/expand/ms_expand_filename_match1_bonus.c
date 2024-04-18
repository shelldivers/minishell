/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filename_match1_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:31:17 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand_bonus.h"
#include "ms_exec_bonus.h"
#include <sys/stat.h>

static t_bool	is_dir(struct dirent *entry, t_glob *glob);

t_bool	ms_match(struct dirent *entry, t_glob *glob)
{
	if (!match_type(entry, glob))
		return (FALSE);
	if (!match_pattern(entry->d_name, glob->pattern))
		return (FALSE);
	return (TRUE);
}

t_bool	match_type(struct dirent *entry, t_glob *glob)
{
	if (ft_strcmp(entry->d_name, ".") == 0)
		return (FALSE);
	if (ft_strcmp(entry->d_name, "..") == 0)
		return (FALSE);
	if (*(glob->rest) == '/' && !is_dir(entry, glob))
		return (FALSE);
	if (*(glob->pattern) != '.' && *(entry->d_name) == '.')
		return (FALSE);
	if (*(glob->pattern) == '.' && *(entry->d_name) != '.')
		return (FALSE);
	return (TRUE);
}

static t_bool	is_dir(struct dirent *entry, t_glob *glob)
{
	struct stat	buf;
	char		*path;
	int			result;

	if (entry->d_type == DT_DIR)
		return (TRUE);
	if (entry->d_type == DT_LNK)
	{
		path = ft_strjoin(glob->path, entry->d_name);
		if (!path)
			return (FALSE);
		result = stat(path, &buf);
		free(path);
		if (result == -1)
			return (FALSE);
		if (s_isdir(buf.st_mode))
			return (TRUE);
	}
	return (FALSE);
}

char	*ms_join_path(t_glob *glob, char *d_name)
{
	char	*str;
	size_t	path_len;
	size_t	entry_len;
	size_t	remain_len;

	path_len = ft_strlen(glob->path);
	entry_len = ft_strlen(d_name);
	remain_len = ft_strlen(glob->rest);
	str = (char *)malloc(path_len + entry_len + remain_len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, glob->path, path_len);
	ft_memcpy(str + path_len, d_name, entry_len);
	ft_memcpy(str + path_len + entry_len, glob->rest, remain_len);
	str[path_len + entry_len + remain_len] = '\0';
	return (str);
}
