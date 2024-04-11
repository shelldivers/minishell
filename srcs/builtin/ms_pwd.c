/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:32:54 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/04 20:32:58 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtin.h"
#include "ms_error.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	ms_pwd(int argc, char **argv, t_env **env)
{
	char	*pwd;

	(void)argc;
	(void)argv;
	pwd = ms_getenv(*env, PWD);
	if (!pwd)
	{
		ms_puterror_cmd(*env, "pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
