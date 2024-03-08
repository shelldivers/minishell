/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:49:07 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/07 10:49:10 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "ms_env.h"
#include "ms_expand.h"
#include <stdlib.h>

static t_bool	ms_expand_env_swap(char **str, char *value, int pre, int suf);

/**
 * @errno ENOMEM
 */
t_bool	ms_expand_env(t_list **node, int *idx, t_env **env, int *exit_code)
{
	int		i;
	char	*key;
	char	*value;
	char	**str;

	i = *idx;
	str = (char **)&((*node)->content);
	ft_memmove((*str) + i, (*str) + i + 1, ft_strlen((*str) + i));
	value = NULL;
	if ((*str)[i] == '?')
		return (ms_expand_reserved(node, idx, exit_code));
	while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == '_'))
		i++;
	key = ft_substr(*str, *idx, i - *idx);
	if (key == NULL)
		return (FALSE);
	value = ms_getenv(*env, key);
	free(key);
	if (!ms_expand_env_swap(str, value, *idx, i))
		return (FALSE);
	*idx = i;
	return (TRUE);
}

/**
 * @errno ENOMEM
 */
t_bool	ms_expand_reserved(t_list **node, int *idx, const int *exit_code)
{
	char	**str;
	char	*nbr;
	t_bool	rtvl;

	str = (char **)&((*node)->content);
	nbr = ft_sprintf("%d", *exit_code);
	if (nbr == NULL)
		return (FALSE);
	rtvl = ms_expand_env_swap(str, nbr, *idx, *idx + 1);
	if (rtvl)
		*idx += (int)ft_strlen(nbr);
	free(nbr);
	return (rtvl);
}

/**
 * @errno ENOMEM
 */
static t_bool	ms_expand_env_swap(char **str, char *value, int pre, int suf)
{
	char	*prefix;
	char	*tmp;
	char	*result;

	if (value == NULL)
		value = "";
	prefix = ft_strndup(*str, pre);
	if (prefix == NULL)
		return (FALSE);
	tmp = ft_strjoin(prefix, value);
	free(prefix);
	if (tmp == NULL)
		return (FALSE);
	result = ft_strjoin(tmp, *str + suf);
	free(tmp);
	if (result == NULL)
		return (FALSE);
	free(*str);
	*str = result;
	return (TRUE);
}
