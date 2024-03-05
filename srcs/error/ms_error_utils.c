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
#include <sys/errno.h>

void	ms_puterror_identifier(t_env *env, char *cmd, char *arg)
{
	char		*shell;
	const char	*msg = "not a valid identifier";

	shell = ms_getenv(env, SHELL);
	ft_dprintf(2, "%s: %s: `%s': %s\n", shell, cmd, arg, msg);
	errno = 0;
}

void	ms_puterror_numeric(t_env *env, char *cmd, char *arg)
{
	char		*shell;
	const char	*msg = "numeric argument required";

	shell = ms_getenv(env, SHELL);
	ft_dprintf(2, "%s: %s: %s: %s\n", shell, cmd, arg, msg);
	errno = 0;
}

void	ms_puterror_too_many_args(t_env *env, char *cmd)
{
	char		*shell;
	const char	*msg = "too many arguments";

	shell = ms_getenv(env, SHELL);
	ft_dprintf(2, "%s: %s: %s\n", shell, cmd, msg);
	errno = 0;
}

void	ms_puterror_env_not_set(t_env *env, char *cmd, char *key)
{
	char		*shell;
	const char	*msg = "not set";

	shell = ms_getenv(env, SHELL);
	ft_dprintf(2, "%s: %s: %s %s\n", shell, cmd, key, msg);
	errno = 0;
}

void	ms_puterror_syntax(t_env **env, char *value)
{
	char		*shell;
	const char	*msg = "syntax error near unexpected value";

	shell = ms_getenv(*env, SHELL);
	ft_dprintf(2, "%s: %s `%s'\n", shell, msg, value);
	errno = 0;
}
