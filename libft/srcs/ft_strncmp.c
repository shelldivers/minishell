/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:40:13 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:05 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*s1_;
	const unsigned char	*s2_;
	size_t				i;

	s1_ = (const unsigned char *)s1;
	s2_ = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_[i] == '\0')
			return (-s2_[i]);
		if (s2_[i] == '\0')
			return (s1_[i]);
		if (s1_[i] != s2_[i])
			return (s1_[i] - s2_[i]);
		i++;
	}
	return (0);
}
