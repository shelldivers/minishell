/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42seoul.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:13:15 by jeongwpa          #+#    #+#             */
/*   Updated: 2023/10/10 17:13:16 by jeongwpa         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*val;

	val = (char *)0;
	while (*s)
	{
		if (*s == (char)c)
			val = (char *)s;
		s++;
	}
	return (val);
}
