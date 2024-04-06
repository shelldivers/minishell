/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_param_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:12:50 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/03 13:03:03 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "ms_env.h"
#include "ms_expand.h"

static size_t	get_key_length(const char *str);
static char		*ms_status_expansion(char *str, char *pos, int status);
static char		*ms_param_expansion(char *str, char *pos, t_env *env);

char	*ms_dollar_expand(char *str, char *pos, int status, t_env *env)
{
	if (pos[1] == '?')
		return (ms_status_expansion(str, pos, status));
	else
		return (ms_param_expansion(str, pos, env));
}

static char	*ms_status_expansion(char *str, char *pos, int status)
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

static char	*ms_param_expansion(char *str, char *pos, t_env *env)
{
	char	*key;
	char	*val;
	char	*tmp;
	char	*tmp2;
	char	*replace;

	key = ft_strndup(pos + 1, get_key_length(pos + 1));
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
	replace = ft_strjoin(tmp2, pos + get_key_length(pos + 1) + 1);
	free(tmp2);
	if (!replace)
		return (NULL);
	return (replace);
}

static size_t	get_key_length(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		if (!ft_isalnum(str[len]) && str[len] != '_')
			return (len);
		len++;
	}
	return (len);
}
