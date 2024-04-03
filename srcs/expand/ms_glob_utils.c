/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_glob_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:13:00 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/03 13:03:17 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"

static t_bool	get_path(t_glob *glob, char **start, char **end, char **pos);
static t_bool	get_pattern(t_glob *glob, char **end, char **pos);
static t_bool	get_rest(t_glob *glob, char **pos);

t_bool	ms_parse_glob(t_glob *glob)
{
	char	*start;
	char	*end;
	char	*pos;

	start = glob->content;
	end = start;
	pos = start;
	get_path(glob, &start, &end, &pos);
	if (!glob->path)
		return (FALSE);
	get_pattern(glob, &end, &pos);
	if (!glob->pattern)
		return (FALSE);
	get_rest(glob, &pos);
	if (!glob->rest)
		return (FALSE);
	return (TRUE);
}

static t_bool	get_path(t_glob *glob, char **start, char **end, char **pos)
{
	while (**pos)
	{
		if (**pos == ASTERISK)
			break ;
		if (**pos == '/')
			*end = *pos;
		(*pos)++;
	}
	if (*start == *end && **end != '/')
		glob->path = ft_strndup(*start, *end - *start);
	else
		glob->path = ft_strndup(*start, *end - *start + 1);
	if (!glob->path)
		return (FALSE);
	return (TRUE);
}

static t_bool	get_pattern(t_glob *glob, char **end, char **pos)
{
	char	*start;

	if (**end == '/')
		(*end)++;
	start = *end;
	while (**pos)
	{
		if (**pos == '/')
			break ;
		(*pos)++;
	}
	*end = *pos;
	glob->pattern = ft_strndup(start, *end - start);
	if (!glob->pattern)
		return (FALSE);
	return (TRUE);
}

static t_bool	get_rest(t_glob *glob, char **pos)
{
	glob->rest = ft_strdup(*pos);
	if (!glob->rest)
		return (FALSE);
	return (TRUE);
}
