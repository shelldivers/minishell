/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:01:56 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/08 15:01:56 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	if (!s1 || !set)
		return (0);
	len = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = len - 1;
	while (j > i && ft_strchr(set, s1[j]))
		j--;
	str = ft_substr(s1, i, j - i + 1);
	return (str);
}
