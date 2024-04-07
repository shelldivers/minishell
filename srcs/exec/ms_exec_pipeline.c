/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:20:34 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/07 19:34:05 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_error.h"
#include "ms_exec.h"
#include <unistd.h>

t_bool	ms_exec_pipe(t_exec *exec_info)
{
	exec_info->pipe_idx++;
	if (pipe(exec_info->pipe[exec_info->pipe_idx % 2]) == -1)
	{
		ms_puterror_cmd(NULL, "pipe");
		return (FALSE);
	}
	return (TRUE);
}

void	ms_dup_pipe(t_exec *exec_info)
{
	ft_dprintf(STDERR_FILENO, "pipe : %d cmd : %d\n", exec_info->pipe_idx, exec_info->cmd_cnt);
	if (exec_info->pipe_idx == 0)
		return ;
	else if (exec_info->pipe_idx == 1)
		ms_dup_first_pipe(exec_info);
	else if (exec_info->pipe_idx == exec_info->cmd_cnt)
		ms_dup_middle_pipe(exec_info);
	if (exec_info->pipe_idx < exec_info->cmd_cnt)
		ms_dup_last_pipe(exec_info);
}

void	ms_close_pipe(t_exec *exec_info)
{
	ft_dprintf(STDERR_FILENO, "pipe : %d cmd : %d\n", exec_info->pipe_idx, exec_info->cmd_cnt);
	if (exec_info->pipe_idx == 0)
		return ;
	else if (exec_info->pipe_idx == 1)
		ms_close_first_pipe(exec_info);
	else if (exec_info->pipe_idx == exec_info->cmd_cnt)
		ms_close_middle_pipe(exec_info);
	else if (exec_info->pipe_idx < exec_info->cmd_cnt)
		ms_close_last_pipe(exec_info);
}

void	ms_dup_first_pipe(t_exec *exec_info)
{
	const int	now_pipe = exec_info->pipe_idx % 2;

	if (dup2(exec_info->pipe[now_pipe][STDOUT_FILENO], STDOUT_FILENO) == -1)
		ms_puterror_cmd(NULL, "dup2");
}

void	ms_dup_middle_pipe(t_exec *exec_info)
{
	const int	now_pipe = exec_info->pipe_idx % 2;
	const int	prev_pipe = (exec_info->pipe_idx + 1) % 2;

	if (dup2(exec_info->pipe[prev_pipe][STDIN_FILENO], STDIN_FILENO) == -1)
		ms_puterror_cmd(NULL, "dup2");
	if (dup2(exec_info->pipe[now_pipe][STDOUT_FILENO], STDOUT_FILENO) == -1)
		ms_puterror_cmd(NULL, "dup2");
}

void	ms_dup_last_pipe(t_exec *exec_info)
{
	const int	now_pipe = exec_info->pipe_idx % 2;

	if (dup2(exec_info->pipe[now_pipe][STDIN_FILENO], STDIN_FILENO) == -1)
		ms_puterror_cmd(NULL, "dup2");
}

void	ms_close_first_pipe(t_exec *exec_info)
{
	const int	now_pipe = exec_info->pipe_idx % 2;
	if (close(exec_info->pipe[now_pipe][STDOUT_FILENO]) == -1)
		ms_puterror_cmd(NULL, "close");
	exec_info->pipe[now_pipe][1] = -1;
}

void	ms_close_middle_pipe(t_exec *exec_info)
{
	const int	now_pipe = exec_info->pipe_idx % 2;
	const int	prev_pipe = (exec_info->pipe_idx + 1) % 2;

	if (close(exec_info->pipe[prev_pipe][STDIN_FILENO]) == -1)
		ms_puterror_cmd(NULL, "close");
	exec_info->pipe[prev_pipe][0] = -1;
	if (close(exec_info->pipe[now_pipe][STDOUT_FILENO]) == -1)
		ms_puterror_cmd(NULL, "close");
	exec_info->pipe[now_pipe][1] = -1;
}

void	ms_close_last_pipe(t_exec *exec_info)
{
	const int	now_pipe = exec_info->pipe_idx % 2;

	if (close(exec_info->pipe[now_pipe][STDIN_FILENO]) == -1)
		ms_puterror_cmd(NULL, "close");
	exec_info->pipe[now_pipe][0] = -1;
}
