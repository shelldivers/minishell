/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:07:40 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/03 17:01:15 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ms_error.h"
#include "ms_exec.h"

static t_bool	ms_close_all_fd2(t_exec *exec_info);

t_bool	ms_close_all_fd(t_exec *exec_info)
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
	return (ms_close_all_fd2(exec_info));
}

//if return false, you must exit(1) and print error message "close"
static t_bool	ms_close_all_fd2(t_exec *exec_info)
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
	return (TRUE);
}

void	ms_reset_io(t_exec *exec_info)
{
	if (dup2(exec_info->origin_fd[0], STDIN_FILENO) == -1)
	{
		write(2, "function : reset_io, dup2\n", 27);
	}
	if (dup2(exec_info->origin_fd[1], STDOUT_FILENO) == -1)
	{
		write(2, "function : reset_io, dup2\n", 27);
	}
}
