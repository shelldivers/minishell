/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:50:25 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:29:17 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_error_bonus.h"
#include "ms_env_bonus.h"
#include "ms_signal_bonus.h"
#include <sys/errno.h>

void	ms_puterror_identifier(t_env *env, char *cmd, char *arg)
{
	const char	*msg = "not a valid identifier";

	(void)env;
	ft_dprintf(2, "%s: %s: `%s': %s\n", MINISHELL, cmd, arg, msg);
	errno = 0;
	g_exit = 1;
}

void	ms_puterror_numeric(t_env *env, char *cmd, char *arg)
{
	const char	*msg = "numeric argument required";

	(void)env;
	ft_dprintf(2, "%s: %s: %s: %s\n", MINISHELL, cmd, arg, msg);
	errno = 0;
	g_exit = 1;
}

void	ms_puterror_too_many_args(t_env *env, char *cmd)
{
	const char	*msg = "too many arguments";

	(void)env;
	ft_dprintf(2, "%s: %s: %s\n", MINISHELL, cmd, msg);
	errno = 0;
	g_exit = 1;
}

void	ms_puterror_env_not_set(t_env *env, char *cmd, char *key)
{
	const char	*msg = "not set";

	(void)env;
	ft_dprintf(2, "%s: %s: %s %s\n", MINISHELL, cmd, key, msg);
	errno = 0;
	g_exit = 1;
}

void	ms_puterror_syntax(t_env **env, char *value)
{
	const char	*msg = "syntax error near unexpected value";

	(void)env;
	ft_dprintf(2, "%s: %s `%s'\n", MINISHELL, msg, value);
	errno = 0;
	g_exit = 258;
}
