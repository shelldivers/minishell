/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:12:55 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/03 13:03:08 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"

void	ms_remove_quote(char *str)
{
	t_bool	dquote;
	t_bool	quote;

	dquote = FALSE;
	quote = FALSE;
	while (*str)
	{
		if (!quote && *str == '\"')
			dquote = (t_bool) !dquote;
		else if (!dquote && *str == '\'')
		{
			quote = (t_bool) !quote;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
			continue ;
		}
		str++;
	}
}

void	ms_remove_dquote(char *str)
{
	char	*_str;
	t_bool	dquote;
	t_bool	quote;

	_str = str;
	dquote = FALSE;
	quote = FALSE;
	while (*_str)
	{
		if (!quote && *_str == '\"')
		{
			dquote = (t_bool) !dquote;
			ft_memmove(_str, _str + 1, ft_strlen(_str) + 1);
			continue ;
		}
		else if (!dquote && *_str == '\'')
			quote = (t_bool) !quote;
		_str++;
	}
}
