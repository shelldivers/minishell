/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:49:01 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/07 10:49:12 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_env.h"
#include "ms_expand.h"

t_bool	ms_expand_quote(t_list **node, int *idx)
{
	char	*str;
	int		i;

	i = *idx;
	str = (char *)(*node)->content;
	ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\'')
		ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
	*idx = i;
	return (TRUE);
}

t_bool	ms_expand_dquote(t_list **node, int *idx, t_env **env, t_exp exp)
{
	char	*str;
	int		i;

	i = *idx;
	str = (char *)(*node)->content;
	ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\\'))
			ms_expand_escape(node, &i);
		else if (str[i] == '$')
			ms_expand_env(node, &i, env, exp.exit_code);
		else
			i++;
	}
	if (str[i] == '\"')
		ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
	*idx = i;
	return (TRUE);
}
