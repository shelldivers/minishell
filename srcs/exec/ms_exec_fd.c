/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:07:40 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/04 20:42:15 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ms_minishell.h"

void	ms_close_all_fd(t_exec *exec_info)
{
	ms_close_pipe(exec_info);
	ms_close_pipe2(exec_info);
	ms_close_stdout(exec_info);
	ms_close_stdin(exec_info);
	if (exec_info->origin_fd[0] != -1)
	{
		if (close(exec_info->origin_fd[0]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info->origin_fd[0] = -1;
	}
	if (exec_info->origin_fd[1] != -1)
	{
		if (close(exec_info->origin_fd[1]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info->origin_fd[1] = -1;
	}
}

void	ms_close_pipe(t_exec *exec_info)
{
	if (exec_info->pipe[0][0] != -1)
	{
		if (close(exec_info->pipe[0][0]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info->pipe[0][0] = -1;
	}
	if (exec_info->pipe[0][1] != -1)
	{
		if (close(exec_info->pipe[0][1]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info->pipe[0][1] = -1;
	}
}

void	ms_close_pipe2(t_exec *exec_info)
{
	if (exec_info->pipe[1][0] != -1)
	{
		if (close(exec_info->pipe[1][0]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info->pipe[1][0] = -1;
	}
	if (exec_info->pipe[1][1] != -1)
	{
		if (close(exec_info->pipe[1][1]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info->pipe[1][1] = -1;
	}
}

void	ms_close_stdout(t_exec *exec_info)
{
	if (exec_info->fd[1] != -1)
	{
		if (close(exec_info->fd[1]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info->fd[1] = -1;
	}
}

void	ms_close_stdin(t_exec *exec_info)
{
	if (exec_info->fd[0] != -1)
	{
		if (close(exec_info->fd[0]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info->fd[0] = -1;
	}
}
