/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:40:13 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:05 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*_s1;
	const unsigned char	*_s2;

	_s1 = (const unsigned char *)s1;
	_s2 = (const unsigned char *)s2;
	while (*_s1 == *_s2)
	{
		if (*_s1 == '\0')
			return (0);
		_s1++;
		_s2++;
	}
	return (*_s1 - *_s2);
}
