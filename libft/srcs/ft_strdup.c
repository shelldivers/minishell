/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:57:28 by jeongwpa          #+#    #+#             */
/*   Updated: 2023/10/11 11:57:28 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!str)
		return (0);
	str[s1_len] = '\0';
	ft_memcpy(str, s1, s1_len);
	return (str);
}
