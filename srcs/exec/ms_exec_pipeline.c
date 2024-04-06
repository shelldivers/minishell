/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:20:34 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/06 19:48:44 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_error.h"
#include "ms_exec.h"
#include <unistd.h>

static void	ms_close_parent_pipe2(\
t_exec *exec_info, int now_pipe);
static void	ms_dup_based_on_pipe_idx2(t_exec *exec_info, const int now_pipe);

t_bool	ms_exec_pipe(t_exec *exec_info)
{
	if (pipe(exec_info->pipe[exec_info->pipe_idx % 2]) == -1)
	{
		ms_puterror_cmd(NULL, "pipe");
		return (FALSE);
	}
	exec_info->pipe_idx++;
	exec_info->pipe_cnt++;
	return (TRUE);
}

void	ms_dup_based_on_pipe_idx(t_exec *exec_info)
{
	const int	now_pipe = (exec_info->pipe_idx + 1) % 2;
	const int	prev_pipe = exec_info->pipe_idx % 2;

	if (exec_info->pipe_cnt == 2)
	{
		if (dup2(exec_info->pipe[prev_pipe][0], STDIN_FILENO) == -1)
			ms_puterror_cmd(NULL, "dup2");
		if (exec_info->fd[1] == -1)
		{
			if (dup2(exec_info->pipe[now_pipe][1], STDOUT_FILENO) == -1)
				ms_puterror_cmd(NULL, "dup2");
		}
	}
	else
		ms_dup_based_on_pipe_idx2(exec_info, now_pipe);
}

static void	ms_dup_based_on_pipe_idx2(t_exec *exec_info, const int now_pipe)
{
	if (exec_info->pipe_cnt == 1 \
	&& exec_info->pipe_idx < exec_info->cmd_cnt)
	{
		if (dup2(exec_info->pipe[now_pipe][STDIN_FILENO], STDIN_FILENO) == -1)
			ms_puterror_cmd(NULL, "dup2");
	}
	else if (exec_info->pipe_cnt == 1 && exec_info->pipe_idx == 1)
	{
		if (exec_info->fd[1] == -1)
		{
			if (dup2(exec_info->pipe[now_pipe][STDOUT_FILENO], \
			STDOUT_FILENO) == -1)
				ms_puterror_cmd(NULL, "dup2");
		}
	}
}

//if return false, you must exec_code = 1 and print error message "close"
void	ms_close_parent_pipe(t_exec *exec_info)
{
	const int	now_pipe = (exec_info->pipe_idx + 1) % 2;
	const int	prev_pipe = exec_info->pipe_idx % 2;

	if (exec_info->pipe_cnt == 2)
	{
		if (close(exec_info->pipe[prev_pipe][STDIN_FILENO]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info->pipe[prev_pipe][0] = -1;
		if (close(exec_info->pipe[now_pipe][STDOUT_FILENO]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info ->pipe[now_pipe][1] = -1;
		exec_info->pipe_cnt--;
	}
	else
		ms_close_parent_pipe2(exec_info, now_pipe);
	if (dup2(exec_info->origin_fd[STDIN_FILENO], STDIN_FILENO) == -1)
		ms_puterror_cmd(NULL, "dup2");
	if (dup2(exec_info->origin_fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
		ms_puterror_cmd(NULL, "dup2");
}

static void	ms_close_parent_pipe2(\
t_exec *exec_info, int now_pipe)
{
	if (exec_info->pipe_cnt == 1 \
	&& exec_info->pipe_idx < exec_info->cmd_cnt)
	{
		if (close(exec_info->pipe[now_pipe][STDIN_FILENO]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info->pipe[now_pipe][STDIN_FILENO] = -1;
	}
	if (exec_info->pipe_cnt == 1 && exec_info->pipe_idx == 1)
	{
		if (close(exec_info->pipe[now_pipe][STDOUT_FILENO]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info->pipe[now_pipe][STDOUT_FILENO] = -1;
	}
}
