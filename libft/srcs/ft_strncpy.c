/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:45:42 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:07 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_strncpy(void *dst, const void *src, size_t n)
{
	char		*dst_;
	const char	*src_;

	if (dst == 0 || src == 0 || n <= 0)
		return ;
	dst_ = (char *)dst;
	src_ = (const char *)src;
	while (n-- > 0)
		*dst_++ = *src_++;
	*dst_ = '\0';
}
