/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:39:30 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:16 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

void	init_format(t_fmt *fmt)
{
	if (!fmt)
		return ;
	fmt->content = 0;
	fmt->length = 0;
	fmt->size = 0;
	fmt->raw_len = 0;
	(fmt->flag).hash = FALSE;
	(fmt->flag).l_adj = FALSE;
	(fmt->flag).padd = ' ';
	(fmt->flag).sign = 0;
	(fmt->flag).width = -1;
	(fmt->flag).prec = -1;
}

static t_fmt	*parse_fmt(t_fmt *fmt, char specifier, va_list ap)
{
	char	*hex_lower;
	char	*hex_upper;

	hex_lower = "0123456789abcdefx";
	hex_upper = "0123456789ABCDEFX";
	if (specifier == '\0')
		return (fmt);
	else if (specifier == 'c')
		return (parse_char(fmt, (char)va_arg(ap, int)));
	else if (specifier == 's')
		return (parse_str(fmt, va_arg(ap, char *)));
	else if (specifier == 'd')
		return (parse_dec(fmt, va_arg(ap, int)));
	else if (specifier == 'i')
		return (parse_int(fmt, va_arg(ap, int)));
	else if (specifier == 'u')
		return (parse_unit(fmt, va_arg(ap, unsigned int)));
	else if (specifier == 'p')
		return (parse_ptr(fmt, va_arg(ap, t_ull), hex_lower));
	else if (specifier == 'x')
		return (parse_hex(fmt, va_arg(ap, unsigned int), hex_lower));
	else if (specifier == 'X')
		return (parse_hex(fmt, va_arg(ap, unsigned int), hex_upper));
	else
		return (parse_char(fmt, specifier));
}

static int	get_digit_str(int *flag, const char *str, int i)
{
	int	ac;
	int	next;

	if (str[i] == '.')
		i++;
	ac = 0;
	while (ft_isdigit(str[i]))
	{
		next = ac * 10 + (str[i++] - '0');
		if (ac > next)
			return (-1);
		ac = next;
	}
	*flag = ac;
	return (i);
}

static t_bool	match_flag(t_fmt *fmt, char flag)
{
	if (flag == '#')
		fmt->flag.hash = TRUE;
	else if (flag == '-')
		fmt->flag.l_adj = TRUE;
	else if (flag == '0')
		fmt->flag.padd = '0';
	else if (flag == '+')
		fmt->flag.sign = '+';
	else if (flag == ' ')
	{
		if (fmt->flag.sign != '+')
			fmt->flag.sign = ' ';
	}
	else
		return (FALSE);
	return (TRUE);
}

t_fmt	*parse_arg(char *str, t_fmt *fmt, va_list ap)
{
	int		i;
	t_bool	is_flag;

	i = 1;
	while (str[i] != '\0' && str[i] != '%' && !ft_isalpha(str[i]))
	{
		if ((str[i] > '0' && str[i] <= '9') || str[i] == '.')
		{
			if (str[i] == '.')
				i = get_digit_str(&fmt->flag.prec, str, i);
			else
				i = get_digit_str(&fmt->flag.width, str, i);
			if (i < 0)
				return (0);
		}
		else
		{
			is_flag = match_flag(fmt, str[i]);
			if (!is_flag)
				break ;
			i++;
		}
	}
	fmt->raw_len = i;
	return (parse_fmt(fmt, str[i], ap));
}
