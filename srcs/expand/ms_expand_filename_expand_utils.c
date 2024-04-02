/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filename_expand_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/02 17:13:12 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"

static t_bool	match_type(struct dirent *entry, t_glob *glob);
static t_bool	match_pattern(char *d_name, char *pattern);

t_bool	ms_match(struct dirent *entry, t_glob *glob)
{
	if (!match_type(entry, glob))
		return (FALSE);
	if (!match_pattern(entry->d_name, glob->pattern))
		return (FALSE);
	return (TRUE);
}

static t_bool	match_type(struct dirent *entry, t_glob *glob)
{
	if (ft_strcmp(entry->d_name, ".") == 0)
		return (FALSE);
	if (ft_strcmp(entry->d_name, "..") == 0)
		return (FALSE);
	if (*(glob->rest) == '/' && entry->d_type != DT_DIR)
		return (FALSE);
	if (*(glob->content) != '.' && *(entry->d_name) == '.')
		return (FALSE);
	return (TRUE);
}

static t_bool	match_pattern(char *d_name, char *pattern)
{
	while (*d_name && *pattern)
	{
		if (*pattern == ASTERISK)
		{
			while (*pattern == ASTERISK)
				pattern++;
			if (!*pattern)
				return (TRUE);
			while (*d_name)
			{
				if (match_pattern(d_name, pattern))
					return (TRUE);
				d_name++;
			}
			return (FALSE);
		}
		if (*d_name != *pattern)
			return (FALSE);
		d_name++;
		pattern++;
	}
	if (*d_name || *pattern)
		return (FALSE);
	return (TRUE);
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
