/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_dup_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:20:34 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 17:56:19 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_error.h"
#include "ms_exec.h"
#include <unistd.h>

void	ms_dup_pipe(t_exec *exec_info)
{
	if (exec_info->pipe_idx == 0)
	{
		ms_close_all_fd(exec_info);
		return ;
	}
	else if (exec_info->pipe_idx < exec_info->cmd_cnt)
		ms_dup_last_pipe(exec_info);
	else if (exec_info->pipe_idx == 1)
		ms_dup_first_pipe(exec_info);
	else if (exec_info->pipe_idx == exec_info->cmd_cnt)
		ms_dup_middle_pipe(exec_info);
	ms_close_all_fd(exec_info);
}

void	ms_dup_first_pipe(t_exec *exec_info)
{
	const int	now = exec_info->pipe_idx % 2;

	if (exec_info->fd[1] == CLOSED)
	{
		if (dup2(exec_info->pipe[now][STDOUT_FILENO], STDOUT_FILENO) == CLOSED)
			ms_puterror_cmd(NULL, "dup2");
	}
}

void	ms_dup_middle_pipe(t_exec *exec_info)
{
	const int	now = exec_info->pipe_idx % 2;
	const int	prev = (exec_info->pipe_idx + 1) % 2;

	if (dup2(exec_info->pipe[prev][STDIN_FILENO], STDIN_FILENO) == CLOSED)
		ms_puterror_cmd(NULL, "dup2");
	if (exec_info->fd[1] == CLOSED)
	{
		if (dup2(exec_info->pipe[now][STDOUT_FILENO], STDOUT_FILENO) == CLOSED)
			ms_puterror_cmd(NULL, "dup2");
	}
}

void	ms_dup_last_pipe(t_exec *exec_info)
{
	const int	now = exec_info->pipe_idx % 2;

	if (exec_info->fd[0] == CLOSED)
	{
		if (dup2(exec_info->pipe[now][STDIN_FILENO], STDIN_FILENO) == CLOSED)
			ms_puterror_cmd(NULL, "dup2");
	}
}
