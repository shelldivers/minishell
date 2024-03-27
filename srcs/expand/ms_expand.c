/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/07 10:49:14 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_expand.h"

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
	char	**expanded;

	if (!ms_expand_param(argv, env, status))
		return (NULL);
	expanded = ms_expand_filename(argv, env);
	if (!expanded)
		return (NULL);
	ms_quote_removal(expanded);
	return (expanded);
}
