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
#include <stdlib.h>

void	ms_expand_tilde(char **argv, t_env *env)
{

}

char	*ms_get_tilde(char *str)
{
	char	*pos;

	pos = ft_strchr(str, '~');
	if (!pos)
		return (NULL);
	if (*(pos + 1) != '\0' && *(pos + 1) != '/')
		return (NULL);
	return (pos);
}

/**
 * @details tilde expansion\n
 * - HOME 환경 변수를 참조하여 확장합니다.\n
 * - HOME 환경 변수가 설정되어 있지 않으면, 빈 문자열로 확장합니다.\n
 * - tilde-prefix는 처리하지 않습니다.
 * @see https://runebook.dev/ko/docs/bash/tilde-expansion
 */
void	ms_tilde_expansion(char **argv, t_env *env)
{
	char	*home;
	int		i;
	char	*pos;

	home = ms_getenv(env, HOME);
	if (!home)
		home = "";
	while (argv)
	{
		pos = ms_get_tilde(*argv);
		if (!pos)
			continue ;
		argv++;
	}
}
