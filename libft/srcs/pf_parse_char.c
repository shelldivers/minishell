/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:58:50 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:19 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static char	*l_adj(t_fmt *fmt, char *str, char arg)
{
	int	i;

	i = 0;
	str[i++] = arg;
	while (i < fmt->size)
		str[i++] = ' ';
	str[fmt->size] = '\0';
	return (str);
}

static char	*r_adj(t_fmt *fmt, char *str, char arg)
{
	int	i;

	i = 0;
	while (i < (fmt->size) - 1)
		str[i++] = fmt->flag.padd;
	str[i] = arg;
	str[fmt->size] = '\0';
	return (str);
}

t_fmt	*parse_char(t_fmt *fmt, char arg)
{
	fmt->size = 1;
	if (fmt->flag.width > 1)
		fmt->size = fmt->flag.width;
	fmt->content = (char *)malloc(sizeof(char) * (fmt->size + 1));
	if (!fmt->content)
		return (0);
	if (fmt->flag.l_adj)
		fmt->content = l_adj(fmt, fmt->content, arg);
	else
		fmt->content = r_adj(fmt, fmt->content, arg);
	return (fmt);
}
