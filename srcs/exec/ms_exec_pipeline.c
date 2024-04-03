/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:20:34 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/03 16:11:01 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ms_exec.h"

//if return false, you must exit(1) and print error message "pipe"
t_bool	ms_exec_pipe(t_ast *ast, t_exec *exec_info)
{
	pipe(exec_info->pipe[exec_info->pipe_idx % 2]);
	exec_info->pipe_idx++;
	exec_info->pipe_cnt++;
	return (TRUE);
}

//if return false, you must exit(1) and print error message "dup2"
t_bool	ms_dup_based_on_pipe_idx(t_exec *exec_info)
{
	const int	now_pipe = (exec_info->pipe_idx + 1) % 2;
	const int	prev_pipe = exec_info->pipe_idx % 2;

	if (exec_info->pipe_cnt == 2)
	{
		dup2(exec_info->pipe[prev_pipe][0], STDIN_FILENO);
		if (exec_info->fd[1] == -1)
			dup2(exec_info->pipe[now_pipe][1], STDOUT_FILENO);
	}
	else if (exec_info->pipe_cnt == 1 \
	&& exec_info->pipe_idx < exec_info->cmd_cnt)
	{
		dup2(exec_info->pipe[now_pipe][STDIN_FILENO], STDIN_FILENO);
	}
	else if (exec_info->pipe_cnt == 1 && exec_info->pipe_idx == 1)
	{
		if (exec_info->fd[1] == -1)
			dup2(exec_info->pipe[now_pipe][STDOUT_FILENO], STDOUT_FILENO);
	}
	return (TRUE);
}

//if return false, you must exec_code = 1 and print error message "close"
t_bool	ms_close_parent_pipe(t_exec *exec_info)
{
	const int	now_pipe = (exec_info->pipe_idx + 1) % 2;
	const int	prev_pipe = exec_info->pipe_idx % 2;

	if (exec_info->pipe_cnt == 2)
	{
		close(exec_info->pipe[prev_pipe][STDIN_FILENO]);
		exec_info->pipe[prev_pipe][0] = -1;
		close(exec_info->pipe[now_pipe][STDOUT_FILENO]);
		exec_info->pipe[now_pipe][1] = -1;
		exec_info->pipe_cnt--;
	}
	else if (exec_info->pipe_cnt == 1 \
	&& exec_info->pipe_idx < exec_info->cmd_cnt)
	{
		close(exec_info->pipe[now_pipe][STDIN_FILENO]);
		exec_info->pipe[now_pipe][STDIN_FILENO] = -1;
	}
	else if (exec_info->pipe_cnt == 1 && exec_info->pipe_idx == 1)
	{
		close(exec_info->pipe[now_pipe][STDOUT_FILENO]);
		exec_info->pipe[now_pipe][STDOUT_FILENO] = -1;
	}
	dup2(exec_info->origin_fd[STDIN_FILENO], STDIN_FILENO);
	dup2(exec_info->origin_fd[STDOUT_FILENO], STDOUT_FILENO);
	return (TRUE);
}
