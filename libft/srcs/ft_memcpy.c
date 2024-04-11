/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:57:30 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:47:52 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_;
	const unsigned char	*src_;
	size_t				i;

	if (dst == 0 && src == 0)
		return (0);
	dst_ = (unsigned char *)dst;
	src_ = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_[i] = src_[i];
		i++;
	}
	return (dst);
}
