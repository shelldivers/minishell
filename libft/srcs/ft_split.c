/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:38:38 by jeongwpa          #+#    #+#             */
/*   Updated: 2023/10/17 11:16:37 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char c)
{
	int	wc;

	if (*s == '\0')
		return (0);
	while (*s == c && *s != '\0')
		s++;
	wc = 0;
	while (*s != '\0')
	{
		if (*s == c && *(s - 1) != c)
			wc++;
		s++;
	}
	if (*(s - 1) != c)
		wc++;
	return (wc);
}

static char	**ft_destroy(char **strs, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	strs = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		wc;
	int		i;
	char	**strs;
	char	*next;

	if (s == 0)
		return (0);
	wc = ft_wordcount(s, c);
	strs = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!strs)
		return (0);
	strs[wc] = NULL;
	i = 0;
	while (i < wc)
	{
		while (*s == c && *s != '\0')
			s++;
		next = ft_strchr(s, c);
		strs[i] = ft_substr(s, 0, next - s);
		if (!strs[i])
			return (ft_destroy(strs, i));
		s = next;
		i++;
	}
	return (strs);
}
