/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:32:56 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:28:52 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtin_bonus.h"
#include "ms_env_bonus.h"
#include "ms_error_bonus.h"
#include <stdlib.h>

int	ms_unset(int argc, char **argv, t_env **env)
{
	int	status;

	if (argc == 1)
		return (EXIT_SUCCESS);
	argv++;
	status = EXIT_SUCCESS;
	while (*argv)
	{
		if (ms_is_valid_env_key(*argv) == FALSE)
		{
			ms_puterror_identifier(*env, "unset", *argv);
			status = EXIT_FAILURE;
		}
		else
			ms_env_remove(env, *argv);
		argv++;
	}
	return (status);
}
