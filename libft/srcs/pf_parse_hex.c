/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:58:59 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:23 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static char	*l_adj(t_fmt *fmt, char *str, char *nbr, char hash)
{
	int	i;

	i = 0;
	if (fmt->flag.hash && fmt->flag.padd == '0')
	{
		str[i++] = '0';
		str[i++] = hash;
	}
	if (fmt->flag.hash && fmt->flag.padd == ' ')
	{
		str[i++] = '0';
		str[i++] = hash;
	}
	while (*nbr != '\0' && i < fmt->size)
		str[i++] = *nbr++;
	while (i < fmt->size)
		str[i++] = ' ';
	str[fmt->size] = '\0';
	return (str);
}

static char	*r_adj(t_fmt *fmt, char *str, char *nbr, char hash)
{
	int	i;
	int	is_sign;

	i = 0;
	is_sign = 0;
	if (fmt->flag.hash && fmt->flag.padd == '0')
	{
		str[i++] = '0';
		str[i++] = hash;
		is_sign = 2;
	}
	while (i < fmt->size - fmt->length + is_sign)
		str[i++] = fmt->flag.padd;
	if (fmt->flag.hash && fmt->flag.padd == ' ')
	{
		str[i++] = '0';
		str[i++] = hash;
	}
	while (*nbr != '\0' && i < fmt->size)
		str[i++] = *nbr++;
	str[fmt->size] = '\0';
	return (str);
}

static char	*utoh_prec(t_fmt *fmt, unsigned int n, const char hex[17])
{
	char			*nbr;
	int				wc;
	unsigned int	m;

	wc = get_udigit(n, 16);
	if (wc < fmt->flag.prec)
		wc = fmt->flag.prec;
	fmt->length = wc;
	nbr = (char *)malloc(sizeof(char) * (wc + 1));
	if (!nbr)
		return (0);
	else if (n == 0)
		nbr[0] = '0';
	nbr[wc] = '\0';
	while (wc-- > 0)
	{
		m = n % 16;
		n = n / 16;
		nbr[wc] = (char)(hex[m]);
	}
	return (nbr);
}

static void	inspect_flag_hex(t_fmt *fmt, unsigned int arg)
{
	if (arg == 0)
		fmt->flag.hash = FALSE;
	if (fmt->flag.prec != -1)
	{
		if (fmt->flag.padd == '0' && fmt->flag.width > fmt->flag.prec)
			fmt->flag.padd = ' ';
	}
	if (fmt->flag.hash)
		fmt->length += 2;
	fmt->size = fmt->flag.width;
	if (fmt->size <= fmt->length)
		fmt->size = fmt->length;
}

t_fmt	*parse_hex(t_fmt *fmt, unsigned int arg, const char hex[17])
{
	char			*nbr;

	if (fmt->flag.prec == 0 && arg == 0)
		nbr = ft_strndup("", 1);
	else
		nbr = utoh_prec(fmt, arg, hex);
	if (!nbr)
		return (0);
	inspect_flag_hex(fmt, arg);
	fmt->content = (char *)malloc(sizeof(char) * (fmt->size + 1));
	if (!fmt->content)
	{
		free(nbr);
		return (0);
	}
	if (fmt->flag.l_adj)
		fmt->content = l_adj(fmt, fmt->content, nbr, hex[16]);
	else
		fmt->content = r_adj(fmt, fmt->content, nbr, hex[16]);
	free(nbr);
	return (fmt);
}
