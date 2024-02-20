/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_dec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:58:54 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:21 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static char	*l_adj(t_fmt *fmt, char *str, char *nbr)
{
	int	i;

	i = 0;
	if (fmt->flag.sign)
		str[i++] = fmt->flag.sign;
	while (*nbr != '\0' && i < fmt->size)
		str[i++] = *nbr++;
	while (i < fmt->size)
		str[i++] = ' ';
	str[fmt->size] = '\0';
	return (str);
}

static char	*r_adj(t_fmt *fmt, char *str, char *nbr)
{
	int	i;
	int	is_sign;

	i = 0;
	is_sign = 0;
	if (fmt->flag.sign && fmt->flag.padd == '0')
	{
		str[i++] = fmt->flag.sign;
		is_sign = 1;
	}
	while (i < fmt->size - fmt->length + is_sign)
		str[i++] = fmt->flag.padd;
	if (fmt->flag.sign && fmt->flag.padd == ' ')
		str[i++] = fmt->flag.sign;
	while (*nbr != '\0' && i < fmt->size)
		str[i++] = *nbr++;
	str[fmt->size] = '\0';
	return (str);
}

static char	*itoa_prec(t_fmt *fmt, int n)
{
	char	*nbr;
	int		wc;
	int		m;
	int		n_flag;

	wc = get_digit(n, 10);
	if (wc < fmt->flag.prec)
		wc = fmt->flag.prec;
	fmt->length = wc;
	nbr = (char *)malloc(sizeof(char) * (wc + 1));
	if (!nbr)
		return (0);
	n_flag = 1;
	if (n < 0)
		n_flag = -1;
	else if (n == 0)
		nbr[0] = '0';
	nbr[wc] = '\0';
	while (wc-- > 0)
	{
		m = n % 10;
		n = n / 10;
		nbr[wc] = (char)('0' + m * n_flag);
	}
	return (nbr);
}

static void	inspect_flag_dec(t_fmt *fmt, int arg)
{
	if (arg < 0)
		fmt->flag.sign = '-';
	if (fmt->flag.prec != -1)
	{
		if (fmt->flag.padd == '0' && fmt->flag.width > fmt->flag.prec)
			fmt->flag.padd = ' ';
	}
	fmt->size = fmt->flag.width;
	if (fmt->flag.sign)
		fmt->length++;
	if (fmt->size <= fmt->length)
		fmt->size = fmt->length;
}

t_fmt	*parse_dec(t_fmt *fmt, const int arg)
{
	char	*nbr;

	if (fmt->flag.prec == 0 && arg == 0)
		nbr = ft_strndup("", 1);
	else
		nbr = itoa_prec(fmt, arg);
	if (!nbr)
		return (0);
	inspect_flag_dec(fmt, arg);
	fmt->content = (char *)malloc(sizeof(char) * (fmt->size + 1));
	if (!fmt->content)
	{
		free(nbr);
		return (0);
	}
	if (fmt->flag.l_adj)
		fmt->content = l_adj(fmt, fmt->content, nbr);
	else
		fmt->content = r_adj(fmt, fmt->content, nbr);
	free(nbr);
	return (fmt);
}
