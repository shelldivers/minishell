/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_dup_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:20:34 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/07 20:50:06 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_error.h"
#include "ms_exec.h"
#include <unistd.h>

void	ms_dup_pipe(t_exec *exec_info)
{
	if (exec_info->pipe_idx == 0)
		return ;
	else if (exec_info->pipe_idx < exec_info->cmd_cnt)
		ms_dup_last_pipe(exec_info);
	else if (exec_info->pipe_idx == 1)
		ms_dup_first_pipe(exec_info);
	else if (exec_info->pipe_idx == exec_info->cmd_cnt)
		ms_dup_middle_pipe(exec_info);
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
