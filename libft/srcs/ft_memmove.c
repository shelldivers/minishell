/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:43:16 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/07 21:50:14 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_;
	const unsigned char	*src_;

	if (dst == src || len == 0)
		return (dst);
	if (dst > src && dst - src < (long)len)
	{
		dst_ = (unsigned char *)dst;
		src_ = (const unsigned char *)src;
		while (len-- > 0)
			dst_[len] = src_[len];
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
