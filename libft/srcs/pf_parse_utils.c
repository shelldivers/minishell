/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:10:32 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:34 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "ft_printf.h"

int	get_udigit(t_ull n, unsigned int base)
{
	int	digit;

	digit = 0;
	while (1)
	{
		n = n / base;
		digit++;
		if (n == 0)
			break ;
	}
	return (digit);
}

int	get_digit(long long n, int base)
{
	int	digit;

	digit = 0;
	while (1)
	{
		n = n / base;
		digit++;
		if (n == 0)
			break ;
	}
	return (digit);
}
