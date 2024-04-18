/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_utils2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:50:25 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:29:21 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_error_bonus.h"
#include "ms_env_bonus.h"
#include "ms_signal_bonus.h"
#include <sys/errno.h>

void	ms_puterror_is_dir(char *path)
{
	const char	*msg = "is a directory";

	ft_dprintf(2, "%s: %s: %s\n", MINISHELL, path, msg);
	errno = 0;
	g_exit = 126;
}

void	ms_puterror_no_file(char *path)
{
	const char	*msg = "No such file or directory";

	ft_dprintf(2, "%s: %s: %s\n", MINISHELL, path, msg);
	errno = 127;
}

void	ms_puterror_fork(void)
{
	const char	*msg = "fork failed";

	ft_dprintf(2, "%s: %s\n", MINISHELL, msg);
	errno = 0;
	g_exit = 1;
}

void	ms_puterror_max_here_doc(void)
{
	const char	*msg = "maximum here-document count exceeded";

	ft_dprintf(2, "%s: %s\n", MINISHELL, msg);
	errno = 0;
	g_exit = 2;
}

void	ms_puterror_no_command(char *path)
{
	const char	*msg = "command not found";

	ft_dprintf(2, "%s: %s: %s\n", MINISHELL, path, msg);
	errno = 0;
	g_exit = 127;
}
