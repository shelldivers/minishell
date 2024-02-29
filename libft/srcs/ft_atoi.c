/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:29:37 by jeongwpa          #+#    #+#             */
/*   Updated: 2023/10/11 11:29:38 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	ac;
	int	n_flag;

	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	n_flag = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		n_flag = -1;
		str++;
	}
	ac = 0;
	while (ft_isdigit(*str))
		ac = ac * 10 + (*str++ - '0') * n_flag;
	return (ac);
}
