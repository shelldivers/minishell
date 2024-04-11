/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:53:21 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/11 14:53:21 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPE_H
# define FT_TYPE_H
# include "ft_bool.h"

typedef unsigned int		t_uint;

typedef unsigned char		t_uchar;

typedef unsigned short		t_ushort;

typedef unsigned long		t_ulong;

typedef unsigned long long	t_ull;

/* libft */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* get_next_line */
typedef struct s_gnl
{
	int				fd;
	char			*content;
	long			length;
	long			size;
	struct s_gnl	*next;
	long			(*read_content)(struct s_gnl *node);
}	t_gnl;

/* ft_printf */
typedef struct s_strs
{
	char			*content;
	int				size;
	struct s_strs	*next;
}	t_strs;

/* ft_printf */
typedef struct s_pflag
{
	t_bool	hash;
	t_bool	l_adj;
	char	padd;
	char	sign;
	int		width;
	int		prec;
}	t_pflag;

/* ft_printf */
typedef struct s_fmt
{
	char			*content;
	int				length;
	int				size;
	int				raw_len;
	struct s_pflag	flag;
}	t_fmt;

#endif
