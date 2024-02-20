/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:59:14 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:30 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static char	*l_adj(t_fmt *fmt, char *str, const char *src)
{
	int	i;
	int	pad_cnt;

	i = 0;
	pad_cnt = i;
	while (*src != '\0' && i < fmt->length + pad_cnt)
		str[i++] = *src++;
	while (i < fmt->size)
		str[i++] = ' ';
	str[fmt->size] = '\0';
	return (str);
}

static char	*r_adj(t_fmt *fmt, char *str, const char *src)
{
	int	i;
	int	pad_cnt;

	i = 0;
	while (i < fmt->size - fmt->length)
		str[i++] = fmt->flag.padd;
	pad_cnt = i;
	while (*src != '\0' && i < fmt->length + pad_cnt)
		str[i++] = *src++;
	str[fmt->size] = '\0';
	return (str);
}

static void	inspect_flag_str(t_fmt *fmt, const char *arg)
{
	fmt->length = (int)ft_strlen(arg);
	if (fmt->flag.prec != -1 && fmt->length > fmt->flag.prec)
		fmt->length = fmt->flag.prec;
	fmt->size = fmt->length;
	if (fmt->flag.width > fmt->length)
		fmt->size = fmt->flag.width;
}

t_fmt	*parse_str(t_fmt *fmt, const char *arg)
{
	if (arg == 0)
		arg = "(null)";
	inspect_flag_str(fmt, arg);
	fmt->content = (char *)malloc(sizeof(char) * (fmt->size + 1));
	if (!fmt->content)
		return (0);
	if (fmt->flag.l_adj)
		fmt->content = l_adj(fmt, fmt->content, arg);
	else
		fmt->content = r_adj(fmt, fmt->content, arg);
	return (fmt);
}
