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

#include "libft.h"
#include "ms_env.h"
#include "ms_error.h"
#include "ms_expand.h"

/**
 * @details quote removal\n
 * - 처리되지 않은 `\`, `"`, `'`를 제거합니다.\n
 * - `\\"`와 `\'`는 `"`와 `'`로 치환합니다.
 * @see https://runebook.dev/ko/docs/bash/quote-removal
 */
t_bool	ms_quote_removal(char **arg)
{

}

/**
 * @details filename expansion\n
 * - `*`를 제외한 다른 특수 패턴을 처리하지 않습니다.
 * @see https://runebook.dev/ko/docs/bash/pattern-matching
 */
char	**ms_filename_expansion(char **arg, t_env *env)
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
	int		i;

	if (!ms_expand_param(argv, env, status))
		return (NULL);
	expanded = ms_filename_expansion(argv, env);
	if (!expanded)
		return (NULL);
	if (!ms_quote_removal(expanded))
	{
		i = 0;
		while (expanded[i])
			free(expanded[i++]);
		free(expanded);
		return (NULL);
	}
	return (expanded);
}
