/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:31:06 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env_bonus.h"
#include "ms_expand_bonus.h"
#include "ms_error_bonus.h"

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
