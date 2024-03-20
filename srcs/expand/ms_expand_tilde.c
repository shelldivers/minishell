/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:49:07 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/07 10:49:10 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"
#include "ms_env.h"
#include "ms_error.h"
#include <stdlib.h>

/**
 * @details tilde expansion\n
 * - HOME 환경 변수를 참조하여 확장합니다.\n
 * - HOME 환경 변수가 설정되어 있지 않으면, 빈 문자열로 확장합니다.\n
 * - tilde-prefix는 처리하지 않습니다.
 * @see https://runebook.dev/ko/docs/bash/tilde-expansion
 */
t_bool	ms_tilde_expansion(char **argv, t_env *env)
{
	char	*home;

	home = ms_getenv(env, HOME);
	if (!home)
		home = "";
	while (argv)
	{
		if (ms_get_tilde(*argv))
		{
			if (!ms_expand_tilde(argv, home, env))
				return (FALSE);
		}
		argv++;
	}
	return (TRUE);
}

t_bool	ms_expand_tilde(char **str, char *home, t_env *env)
{
	char	*tmp;

	tmp = ft_strjoin(home, (*str) + 1);
	if (!tmp)
	{
		ms_puterror_arg(env, "~");
		return (FALSE);
	}
	free(*str);
	*str = tmp;
	return (TRUE);
}

t_bool	ms_get_tilde(const char *str)
{
	if ((*str) != '~')
		return (FALSE);
	if (*(str + 1) != '\0' && *(str + 1) != '/')
		return (FALSE);
	return (TRUE);
}
