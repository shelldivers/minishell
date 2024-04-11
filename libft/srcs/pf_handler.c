/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:44:38 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:47:57 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static char	*fmtlstadd_from_arg(t_strs **head, va_list ap, char *str, int i)
{
	t_strs	*node;
	t_fmt	fmt;

	init_format(&fmt);
	if (!parse_arg(str + i, &fmt, ap))
		return (0);
	node = strs_new(fmt.content, fmt.size);
	if (!node)
	{
		free(fmt.content);
		return (0);
	}
	strs_add_back(head, node);
	if (*(str + i + fmt.raw_len) == '\0')
		return (str + i + fmt.raw_len);
	return (str + i + fmt.raw_len + 1);
}

static char	*fmtlstadd_from_str(t_strs **head, char *str, int i)
{
	t_strs	*node;
	char	*sub;

	if (i == 0)
		return (str);
	sub = ft_strndup(str, i);
	if (!sub)
		return (0);
	node = strs_new(sub, i);
	if (!node)
	{
		free(sub);
		return (0);
	}
	strs_add_back(head, node);
	return (str);
}

static char	*fmtlstadd_handler(t_strs **head, va_list ap, char *str, int i)
{
	char	*next;

	next = fmtlstadd_from_str(head, (char *)str, i);
	if (!next)
	{
		strs_clear(head);
		return (0);
	}
	next = fmtlstadd_from_arg(head, ap, (char *)str, i);
	if (!next)
	{
		strs_clear(head);
		return (0);
	}
	return (next);
}

t_bool	get_fmtlst(t_strs **head, const char *fmt, va_list ap)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)fmt;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			str = fmtlstadd_handler(head, ap, (char *)str, i);
			if (!str)
				return (FALSE);
			i = 0;
		}
		else
			i++;
	}
	str = fmtlstadd_from_str(head, (char *)str, i);
	if (!str)
	{
		strs_clear(head);
		return (FALSE);
	}
	return (TRUE);
}
