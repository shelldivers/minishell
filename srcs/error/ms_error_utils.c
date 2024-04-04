/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:50:25 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/04 20:49:10 by jiwojung         ###   ########.fr       */
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

void	ms_puterror_is_dir(char *path)
{
	const char	*msg = "is a directory";

	ft_dprintf(2, "minishell: %s: %s\n", path, msg);
	errno = 0;
}

void	ms_puterror_no_file(char *path)
{
	const char	*msg = "No such file or directory";

	ft_dprintf(2, "minishell: %s: %s\n", path, msg);
	errno = 0;
}

void	ms_puterror_fork(void)
{
	const char	*msg = "fork failed";

	ft_dprintf(2, "minishell: %s\n", msg);
	errno = 0;
}

void	ms_puterror_max_here_doc(void)
{
	const char	*msg = "maximum here-document count exceeded";

	ft_dprintf(2, "minishell: %s\n", msg);
	errno = 0;
}

void	ms_puterror_no_command(char *path)
{
	const char	*msg = "command not found";

	ft_dprintf(2, "minishell: %s: %s\n", path, msg);
	errno = 0;
}
