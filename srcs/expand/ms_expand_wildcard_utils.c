/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_wildcard_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:57 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/07 10:49:13 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"
#include <stdlib.h>

/**
 * @errno ENOMEM
 */
char	*ms_wildcard_get_path(char *str)
{
	char	*path_end;
	int		i;

	i = 0;
	while (str[i] && str[i] != '*')
	{
		if (str[i] == '/')
			path_end = str + i;
		i++;
	}
	if (i == 0)
		return (ft_strdup("."));
	return (ft_strndup(str, path_end - str + 1));
}

char	*ms_wildcard_get_last(char *str)
{
	char	*remain;
	int		i;

	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	while (str[i])
	{
		if (str[i] == '/')
		{
			remain = str + i;
			break ;
		}
		i++;
	}
	if (str[i] == '\0')
		return (ft_strdup(""));
	return (ft_strdup(remain));
}

/**
 * @errno ENOMEM
 */
char	*ms_wildcard_get_prefix(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '*')
	{
		if (str[i] == '/')
		{
			str = str + i + 1;
			i = 0;
		}
		else
			i++;
	}
	if (i == 0)
		return (ft_strdup(""));
	return (ft_strndup(str, i));
}

/**
 * @errno ENOMEM
 */
char	*ms_wildcard_get_suffix(char *str)
{
	int		i;
	int		len;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			break ;
		i++;
	}
	if (str[i] == '\0' || str[i + 1] == '/')
		return (ft_strdup(""));
	len = 0;
	while (str[i + len + 1] && str[i + len + 1] != '/')
		len++;
	return (ft_strndup(str + i + 1, len));
}

/**
 * @errno ENOMEM
 */
char	*ms_wildcard_combine(char *d_name, char *path, char *last)
{
	char	*name;
	char	*tmp;

	tmp = ft_strjoin(d_name, last);
	if (!tmp)
		return (NULL);
	if (ft_strcmp(path, ".") == 0 || ft_strcmp(path, "..") == 0)
		return (tmp);
	name = ft_strjoin(path, tmp);
	free(tmp);
	return (name);
}
