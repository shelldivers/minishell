/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/05 14:05:11 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_expand.h"
#include "ms_error.h"

/**
 * @details 쉘 확장은 다음 순서로 진행됩니다.\n
 * parameter expansion -> filename expansion -> quote removal
 * @see https://runebook.dev/ko/docs/bash/shell-expansions
 */
char	**ms_expansion(char **argv, t_env *env)
{
	char	**copy;
	char	**expanded;
	int		i;

	copy = ms_expand_params(argv, env);
	if (!copy)
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
	return (expanded);
}
