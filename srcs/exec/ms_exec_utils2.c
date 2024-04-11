/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:25:35 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/06 20:08:05 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_error.h"
#include "ms_exec.h"
#include "ms_signal.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	ms_set_exited(int status)
{
	int	signum;

	if (wifexit(status) == TRUE)
		g_exit = wexitstatus(status);
	else if (wifsignaled(status) == TRUE)
	{
		signum = wstatus(status);
		if (signum == SIGINT)
			ft_dprintf(STDERR_FILENO, "\n");
		else if (signum == SIGQUIT)
			ft_dprintf(STDERR_FILENO, "Quit: 3\n");
		g_exit = 128 + signum;
	}
}

void	dup2_fd(t_exec *exec_info)
{
	const int	seq = exec_info->heredoc_seq - 1;

	if (exec_info->fd[0] != -1)
	{
		if (dup2(exec_info->fd[0], STDIN_FILENO) == -1)
			ms_puterror_cmd(NULL, "dup2");
	}
	else if (exec_info->fd[0] == -1 && seq >= 0 \
	&& exec_info->heredoc_fd[seq] > 0)
	{
		if (dup2(exec_info->heredoc_fd[seq], STDIN_FILENO) == -1)
			ms_puterror_cmd(NULL, "dup2");
	}
	if (exec_info->fd[1] != -1)
		if (dup2(exec_info->fd[1], STDOUT_FILENO) == -1)
			ms_puterror_cmd(NULL, "dup2");
}
