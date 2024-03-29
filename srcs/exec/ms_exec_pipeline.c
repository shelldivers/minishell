/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:07:40 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/29 20:25:45 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ms_env.h"
#include "ms_builtin.h"
#include "minishell.h"

//if return false, you must exit(1) and print error message "close"
t_bool	ms_close_fd(t_exec *exec_info)
{
	if (exec_info->fd[0] != -1)
	{
		if (close(exec_info->fd[0]) == -1)
			return (FALSE);
		exec_info->fd[0] = -1;
	}
	if (exec_info->fd[1] != -1)
	{
		if (close(exec_info->fd[1]) == -1)
			return (FALSE);
		exec_info->fd[1] = -1;
	}
	dup2(exec_info->origin_fd[0], STDIN_FILENO);
	dup2(exec_info->origin_fd[1], STDOUT_FILENO);
	return (TRUE);
}

t_bool	ms_reset_fd(t_exec *exec_info)
{
	const int	now_pipe = (exec_info->pipe_idx + 1) % 2;
	const int	prev_pipe = exec_info->pipe_idx % 2;

	if (exec_info->pipe_cnt == 2)
	{
		if (close(exec_info->pipe[prev_pipe][1]) == -1)
			return (FALSE);
		exec_info->pipe[prev_pipe][1] = -1;
		if (close(exec_info->pipe[now_pipe][0]) == -1)
			return (FALSE);
		exec_info->pipe[now_pipe][0] = -1;
		if (close(exec_info->pipe[now_pipe][1]) == -1)
			return (FALSE);
		exec_info->pipe[now_pipe][1] = -1;
	}
	else if (exec_info->pipe_cnt == 1)
	{
		if (close(exec_info->pipe[now_pipe][0]) == -1)
			return (FALSE);
		exec_info->pipe[now_pipe][0] = -1;
		exec_info->pipe_cnt--;
	}
	return (ms_close_fd(exec_info));
}

//if return false, you must exec_code = 1 and print error message "close"
t_bool	ms_close_parent_pipe(t_exec *exec_info)
{
	const int	now_pipe = (exec_info->pipe_idx + 1) % 2;
	const int	prev_pipe = exec_info->pipe_idx % 2;

	if (exec_info->pipe_cnt == 2)
	{
		if (close(exec_info->pipe[prev_pipe][0]) == -1)
			return (FALSE);
		exec_info->pipe[prev_pipe][0] = -1;
		if (close(exec_info->pipe[now_pipe][1]) == -1)
			return (FALSE);
		exec_info->pipe[now_pipe][1] = -1;
		exec_info->pipe_cnt--;
	}
	else if (exec_info->pipe_cnt == 1)
	{
		if (close(exec_info->pipe[now_pipe][1]) == -1)
			return (FALSE);
		exec_info->pipe[now_pipe][1] = -1;
	}
	return (TRUE);
}

//if return false, you must exit(1) and print error message "dup2"
t_bool	ms_dup_based_on_pipe_idx(t_exec *exec_info)
{
	const int	now_pipe = (exec_info->pipe_idx + 1) % 2;
	const int	prev_pipe = exec_info->pipe_idx % 2;

	if (exec_info->pipe_cnt == 2)
	{
		if (dup2(exec_info->pipe[prev_pipe][0], STDIN_FILENO) == -1)
			return (FALSE);
		if (dup2(exec_info->pipe[now_pipe][1], STDOUT_FILENO) == -1)
			return (FALSE);
	}
	else if (exec_info->pipe_cnt == 1 \
	&& exec_info->pipe_idx < exec_info->cmd_cnt)
	{
		if (dup2(exec_info->pipe[now_pipe][0], STDIN_FILENO) == -1)
			return (FALSE);
	}
	else if (exec_info->pipe_cnt == 1 && exec_info->pipe_idx == 1)
	{
		if (dup2(exec_info->pipe[now_pipe][1], STDOUT_FILENO) == -1)
			return (FALSE);
	}
	return (TRUE);
}

//if return false, you must exit(1) and print error message "pipe"
t_bool	ms_exec_pipe(t_ast *ast, t_exec *exec_info, t_env **env)
{
	if (pipe(exec_info->pipe[exec_info->pipe_idx % 2]) == -1)
		return (FALSE);
	exec_info->pipe_idx++;
	exec_info->pipe_cnt++;
	return (TRUE);
}
