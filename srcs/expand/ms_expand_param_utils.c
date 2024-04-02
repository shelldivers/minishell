/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_param_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:12:50 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/02 17:13:10 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "ms_env.h"
#include "ms_expand.h"

static size_t	ft_strcspn(const char *str, const char *charset);

char	*ms_status_expansion(char *str, char *pos, int status)
{
	char	*nbr;
	char	*tmp;
	char	*tmp2;
	char	*replace;

	nbr = ft_sprintf("%d", status);
	if (!nbr)
		return (NULL);
	tmp = ft_strndup(str, pos - str);
	if (!tmp)
	{
		free(nbr);
		return (NULL);
	}
	tmp2 = ft_strjoin(tmp, nbr);
	free(tmp);
	free(nbr);
	if (!tmp2)
		return (NULL);
	replace = ft_strjoin(tmp2, pos + 2);
	free(tmp2);
	if (!replace)
		return (NULL);
	return (replace);
}

char	*ms_param_expansion(char *str, char *pos, t_env *env)
{
	char	*key;
	char	*val;
	char	*tmp;
	char	*tmp2;
	char	*replace;

	key = ft_strndup(pos + 1, ft_strcspn(pos + 1, " \t\n\"'\\$"));
	if (!key)
		return (NULL);
	val = ms_getenv(env, key);
	free(key);
	if (!val)
		val = "";
	tmp = ft_strndup(str, pos - str);
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(tmp, val);
	free(tmp);
	if (!tmp2)
		return (NULL);
	replace = ft_strjoin(tmp2, pos + ft_strcspn(pos + 1, " \t\n\"'\\$") + 1);
	free(tmp2);
	if (!replace)
		return (NULL);
	return (replace);
}

static size_t	ft_strcspn(const char *str, const char *charset)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (charset[j])
		{
			if (str[i] == charset[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}