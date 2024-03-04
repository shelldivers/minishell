/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:32:52 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/04 20:32:59 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_builtin.h"
#include "ms_error.h"
#include <stdlib.h>
#include <unistd.h>

int	ms_exit(int argc, char **argv, t_env **env)
{
	char	exit_code;

	(void)argc;
	argv++;
	if (*argv == NULL)
		exit_code = 0;
	else
	{
		if (ft_isnumeric(*argv) == 0)
		{
			ms_puterror_numeric(*env, "exit", *argv);
			exit(255);
		}
		if (*(argv + 1) != NULL)
		{
			ms_puterror_too_many_args(*env, "exit");
			return (EXIT_FAILURE);
		}
		exit_code = (char)ft_atoi(*argv);
	}
	write(1, "exit\n", 5);
	exit(exit_code);
}
