/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:07:40 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 16:28:27 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_error.h"
#include "ms_exec.h"
#include <unistd.h>

void	ms_close_all_fd(t_exec *exec_info)
{
	ms_close_all_pipe(exec_info);
	ms_close_all_pipe2(exec_info);
	ms_close_stdout(exec_info);
	ms_close_stdin(exec_info);
	if (exec_info->origin_fd[0] != CLOSED)
	{
		if (close(exec_info->origin_fd[0]) == CLOSED)
			ms_puterror_cmd(NULL, "close");
		exec_info->origin_fd[0] = CLOSED;
	}
	if (exec_info->origin_fd[1] != CLOSED)
	{
		if (close(exec_info->origin_fd[1]) == CLOSED)
			ms_puterror_cmd(NULL, "close");
		exec_info->origin_fd[1] = CLOSED;
	}
}

void	ms_close_all_pipe(t_exec *exec_info)
{
	if (exec_info->pipe[0][0] != CLOSED)
	{
		if (close(exec_info->pipe[0][0]) == CLOSED)
			ms_puterror_cmd(NULL, "close");
		exec_info->pipe[0][0] = CLOSED;
	}
	if (exec_info->pipe[0][1] != CLOSED)
	{
		if (close(exec_info->pipe[0][1]) == CLOSED)
			ms_puterror_cmd(NULL, "close");
		exec_info->pipe[0][1] = CLOSED;
	}
}

void	ms_close_all_pipe2(t_exec *exec_info)
{
	if (exec_info->pipe[1][0] != CLOSED)
	{
		if (close(exec_info->pipe[1][0]) == CLOSED)
			ms_puterror_cmd(NULL, "close");
		exec_info->pipe[1][0] = CLOSED;
	}
	if (exec_info->pipe[1][1] != CLOSED)
	{
		if (close(exec_info->pipe[1][1]) == CLOSED)
			ms_puterror_cmd(NULL, "close");
		exec_info->pipe[1][1] = CLOSED;
	}
}

void	ms_close_stdout(t_exec *exec_info)
{
	if (exec_info->fd[1] != CLOSED)
	{
		if (close(exec_info->fd[1]) == CLOSED)
			ms_puterror_cmd(NULL, "close");
		exec_info->fd[1] = CLOSED;
	}
}

void	ms_close_stdin(t_exec *exec_info)
{
	if (exec_info->fd[0] != CLOSED)
	{
		if (close(exec_info->fd[0]) == CLOSED)
			ms_puterror_cmd(NULL, "close");
		exec_info->fd[0] = CLOSED;
	}
}
