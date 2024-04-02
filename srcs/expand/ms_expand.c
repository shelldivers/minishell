/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/02 17:13:08 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_env.h"
#include "ms_expand.h"
#include "ms_error.h"

char	**ms_strsdup(char **strs)
{
	char	**copy;
	size_t	size;
	size_t	i;

	size = 0;
	while (strs[size])
		size++;
	copy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (strs[i] && i < size)
	{
		copy[i] = ft_strdup(strs[i]);
		if (!copy[i])
		{
			while (i--)
				free(copy[i]);
			return (NULL);
		}
		i++;
	}
	copy[size] = NULL;
	return (copy);
}

/**
 * @details quote removal\n
 * - 처리되지 않은 `\`, `"`, `'`를 제거합니다.\n
 * - `\\"`와 `\'`는 `"`와 `'`로 치환합니다.
 * @see https://runebook.dev/ko/docs/bash/quote-removal
 */
void	ms_quote_removal(char **argv)
{
}

/**
 * @details 쉘 확장은 다음 순서로 진행됩니다.\n
 * parameter expansion -> filename expansion -> quote removal
 * @see https://runebook.dev/ko/docs/bash/shell-expansions
 */
char	**ms_expansion(char **argv, t_env *env, int status)
{
	char	**copy;
	char	**expanded;
	int		i;

	copy = ms_strsdup(argv);
	if (!copy)
		return (NULL);
	if (!ms_expand_param(copy, env, status))
		return (NULL);
	expanded = ms_expand_filenames(copy);
	i = 0;
	while (copy[i])
		free(copy[i++]);
	free(copy);
	if (!expanded)
	{
		ms_puterror_arg(env, *argv);
		return (NULL);
	}
	ms_quote_removal(expanded);
	return (expanded);
}
