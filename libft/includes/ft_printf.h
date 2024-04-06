/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:26:58 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/11 14:52:59 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BUFFER_SIZE 512
# include "ft_bool.h"
# include "ft_type.h"
# include <stdarg.h>

/* ft_printf.c */
int		ft_printf(const char *str, ...);
int		ft_dprintf(int fd, const char *str, ...);
char	*ft_sprintf(const char *str, ...);

/* handler.c */
t_bool	get_fmtlst(t_strs **head, const char *fmt, va_list ap);

/* format.c */
void	init_format(t_fmt *fmt);
t_fmt	*parse_arg(char *str, t_fmt *fmt, va_list ap);

/* parse_utils.c */
int		get_udigit(t_ull n, unsigned int base);
int		get_digit(long long n, int base);

/* parse_char.c */
t_fmt	*parse_char(t_fmt *fmt, char arg);

/* parse_str.c */
t_fmt	*parse_str(t_fmt *fmt, const char *str);

/* parse_dec.c */
t_fmt	*parse_dec(t_fmt *fmt, int arg);

/* parse_int.c */
t_fmt	*parse_int(t_fmt *fmt, int arg);

/* parse_unit.c */
t_fmt	*parse_unit(t_fmt *fmt, unsigned int arg);

/* parse_ptr.c */
t_fmt	*parse_ptr(t_fmt *fmt, t_ull arg, const char hex[17]);

/* parse_hex.c */
t_fmt	*parse_hex(t_fmt *fmt, unsigned int arg, const char hex[17]);

/* strs_utils.c */
void	strs_add_back(t_strs **lst, t_strs *new_node);
void	strs_clear(t_strs **lst);
t_strs	*strs_new(char *content, int size);

#endif
