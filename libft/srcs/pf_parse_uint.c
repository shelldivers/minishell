/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:59:17 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:32 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static char	*l_adj(t_fmt *fmt, char *str, char *nbr)
{
	int	i;

	i = 0;
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

	i = 0;
	while (i < fmt->size - fmt->length)
		str[i++] = fmt->flag.padd;
	while (*nbr != '\0' && i < fmt->size)
		str[i++] = *nbr++;
	str[fmt->size] = '\0';
	return (str);
}

static char	*utoa_prec(t_fmt *fmt, unsigned int n)
{
	char			*nbr;
	int				wc;
	unsigned int	m;

	wc = get_udigit(n, 10);
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
		m = n % 10;
		n = n / 10;
		nbr[wc] = (char)('0' + m);
	}
	return (nbr);
}

static void	inspect_flag_uint(t_fmt *fmt)
{
	if (fmt->flag.prec != -1)
	{
		if (fmt->flag.padd == '0' && fmt->flag.width > fmt->flag.prec)
			fmt->flag.padd = ' ';
	}
	fmt->size = fmt->flag.width;
	if (fmt->size <= fmt->length)
		fmt->size = fmt->length;
}

t_fmt	*parse_unit(t_fmt *fmt, unsigned int arg)
{
	char	*nbr;

	if (fmt->flag.prec == 0 && arg == 0)
		nbr = ft_strndup("", 1);
	else
		nbr = utoa_prec(fmt, arg);
	if (!nbr)
		return (0);
	inspect_flag_uint(fmt);
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
