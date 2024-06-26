/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_open_close_pipe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:20:34 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 16:36:30 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_error.h"
#include "ms_exec.h"
#include "ms_signal.h"
#include <unistd.h>

t_bool	ms_exec_pipe(t_exec *exec_info)
{
	exec_info->pipe_idx++;
	if (pipe(exec_info->pipe[exec_info->pipe_idx % 2]) == FAILED)
	{
		ms_puterror_cmd(NULL, "pipe");
		return (FALSE);
	}
	return (TRUE);
}

void	ms_close_pipe(t_exec *exec_info)
{
	if (exec_info->pipe_idx == 0)
		return ;
	else if (exec_info->pipe_idx < exec_info->cmd_cnt)
		ms_close_last_pipe(exec_info);
	else if (exec_info->pipe_idx == 1)
		ms_close_first_pipe(exec_info);
	else if (exec_info->pipe_idx == exec_info->cmd_cnt)
		ms_close_middle_pipe(exec_info);
}

void	ms_close_first_pipe(t_exec *exec_info)
{
	const int	now = exec_info->pipe_idx % 2;

	if (close(exec_info->pipe[now][STDOUT_FILENO]) == FAILED)
		ms_puterror_cmd(NULL, "close");
	exec_info->pipe[now][1] = CLOSED;
}

void	ms_close_middle_pipe(t_exec *exec_info)
{
	const int	now = exec_info->pipe_idx % 2;
	const int	prev = (exec_info->pipe_idx + 1) % 2;

	if (close(exec_info->pipe[prev][STDIN_FILENO]) == FAILED)
		ms_puterror_cmd(NULL, "close");
	exec_info->pipe[prev][0] = CLOSED;
	if (close(exec_info->pipe[now][STDOUT_FILENO]) == FAILED)
		ms_puterror_cmd(NULL, "close");
	exec_info->pipe[now][1] = CLOSED;
}

void	ms_close_last_pipe(t_exec *exec_info)
{
	const int	now = exec_info->pipe_idx % 2;

	if (close(exec_info->pipe[now][STDIN_FILENO]) == FAILED)
		ms_puterror_cmd(NULL, "close");
	exec_info->pipe[now][0] = CLOSED;
}
