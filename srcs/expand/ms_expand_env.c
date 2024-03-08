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

#include "libft.h"
#include "ms_env.h"
#include "ms_expand.h"
#include <stdlib.h>

static t_bool	ms_expand_env_exchange(char **str, int *index, char *value);

/**
 * @errno ENOMEM
 */
t_bool	ms_expand_env(t_list **node, int *idx, t_env **env)
{
	int		i;
	char	*key;
	char	*value;
	char	**str;

	i = *idx;
	str = (char **)&((*node)->content);
	ft_memmove((*str) + i, (*str) + i + 1, ft_strlen((*str) + i));
	while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == '_'))
		i++;
	key = ft_substr(*str, *idx, i - *idx);
	if (key == NULL)
		return (FALSE);
	value = ms_getenv(*env, key);
	free(key);
	if (value == NULL)
		value = "";
	if (!ms_expand_env_exchange(str, idx, value))
		return (FALSE);
	return (TRUE);
}

/**
 * @errno ENOMEM
 */
static t_bool	ms_expand_env_exchange(char **str, int *index, char *value)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strndup(*str, *index);
	if (tmp == NULL)
		return (FALSE);
	tmp2 = ft_strjoin(tmp, value);
	free(tmp);
	if (tmp2 == NULL)
		return (FALSE);
	*index = (int)ft_strlen(tmp2);
	tmp = ft_strjoin(tmp2, *str + *index);
	free(tmp2);
	if (tmp == NULL)
		return (FALSE);
	free(*str);
	*str = tmp;
	return (TRUE);
}
