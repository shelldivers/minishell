/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:50:25 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:29:12 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_error_bonus.h"
#include "ms_env_bonus.h"
#include "ms_signal_bonus.h"
#include <string.h>
#include <sys/errno.h>

void	ms_puterror_cmd_arg(t_env *env, char *cmd, char *arg)
{
	char	*str_error;

	(void)env;
	str_error = strerror(errno);
	ft_dprintf(2, "%s: %s: %s: %s\n", MINISHELL, cmd, arg, str_error);
	errno = 0;
	g_exit = 1;
}

void	ms_puterror_cmd(t_env *env, char *cmd)
{
	char	*str_error;

	(void)env;
	str_error = strerror(errno);
	ft_dprintf(2, "%s: %s: %s\n", MINISHELL, cmd, str_error);
	errno = 0;
	g_exit = 1;
}

void	ms_puterror_arg(t_env *env, char *arg)
{
	char	*str_error;

	(void)env;
	str_error = strerror(errno);
	ft_dprintf(2, "%s: %s: %s\n", MINISHELL, arg, str_error);
	errno = 0;
	g_exit = 1;
}
