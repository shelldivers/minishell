/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:50:25 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/04 20:00:59 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_error.h"
#include "ms_env.h"
#include <string.h>
#include <sys/errno.h>

void	ms_puterror_cmd_arg(t_env *env, char *cmd, char *arg)
{
	char	*str_error;

	(void)env;
	str_error = strerror(errno);
	ft_dprintf(2, "%s: %s: %s: %s\n", "minishell", cmd, arg, str_error);
	errno = 0;
}

void	ms_puterror_cmd(t_env *env, char *cmd)
{
	char	*str_error;

	(void)env;
	str_error = strerror(errno);
	ft_dprintf(2, "%s: %s: %s\n", "minishell", cmd, str_error);
	errno = 0;
}

void	ms_puterror_arg(t_env *env, char *arg)
{
	char	*str_error;

	(void)env;
	str_error = strerror(errno);
	ft_dprintf(2, "%s: %s: %s\n", "minishell", arg, str_error);
	errno = 0;
}
