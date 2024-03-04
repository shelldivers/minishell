/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:50:25 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/04 18:50:26 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_error.h"
#include "ms_env.h"
#include <string.h>
#include <sys/errno.h>

void	ms_puterror_cmd_arg(t_env *env, char *cmd, char *arg)
{
	char	*shell;
	char	*str_error;

	shell = ms_getenv(env, SHELL);
	str_error = strerror(errno);
	ft_dprintf(2, "%s: %s: %s: %s\n", shell, cmd, arg, str_error);
}

void	ms_puterror_cmd(t_env *env, char *cmd)
{
	char	*shell;
	char	*str_error;

	shell = ms_getenv(env, SHELL);
	str_error = strerror(errno);
	ft_dprintf(2, "%s: %s: %s\n", shell, cmd, str_error);
}

void	ms_puterror_arg(t_env *env, char *arg)
{
	char	*shell;
	char	*str_error;

	shell = ms_getenv(env, SHELL);
	str_error = strerror(errno);
	ft_dprintf(2, "%s: %s: %s\n", shell, arg, str_error);
}
