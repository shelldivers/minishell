/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:13:00 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/03 13:03:21 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"

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
