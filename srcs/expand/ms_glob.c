/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:13:00 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/02 17:13:07 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"

t_bool	ms_parse_glob(t_glob *glob)
{
	char	*start;
	char	*end;
	char	*pos;

	start = glob->content;
	end = start;
	pos = start;
	while (*pos)
	{
		if (*pos == ASTERISK)
			break ;
		if (*pos == '/')
			end = pos;
		pos++;
	}
	glob->path = ft_strndup(start, end - start + 1);
	if (!glob->path)
		return (FALSE);
	start = end + 1;
	while (*pos)
	{
		if (*pos == '/')
			break ;
		pos++;
	}
	end = pos;
	glob->pattern = ft_strndup(start, end - start);
	if (!glob->pattern)
		return (FALSE);
	glob->rest = ft_strdup(pos);
	if (!glob->rest)
		return (FALSE);
	return (TRUE);
}

t_glob	*ms_init_glob(char *str)
{
	t_glob	*glob;

	glob = (t_glob *)malloc(sizeof(t_glob));
	if (!glob)
		return (NULL);
	ft_memset(glob, 0, sizeof(t_glob));
	glob->content = ft_strdup(str);
	if (!glob->content)
	{
		ms_destroy_glob(glob);
		return (NULL);
	}
	if (!ms_parse_glob(glob))
	{
		ms_destroy_glob(glob);
		return (NULL);
	}
	return (glob);
}

void	ms_destroy_glob(t_glob *glob)
{
	if (glob->content)
		free(glob->content);
	if (glob->pattern)
		free(glob->pattern);
	if (glob->path)
		free(glob->path);
	if (glob->rest)
		free(glob->rest);
	free(glob);
}
