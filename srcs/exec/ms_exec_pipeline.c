/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:20:34 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/02 19:21:33 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ms_env.h"
#include "ms_builtin.h"
#include "minishell.h"

//if return false, you must exit(1) and print error message "pipe"
t_bool	ms_exec_pipe(t_ast *ast, t_exec *exec_info, t_env **env)
{
	if (pipe(exec_info->pipe[exec_info->pipe_idx % 2]) == -1)
		return (FALSE);
	exec_info->pipe_idx++;
	exec_info->pipe_cnt++;
	return (TRUE);
}

//if return false, you must exit(1) and print error message "dup2"
t_bool	ms_dup_based_on_pipe_idx(t_exec *exec_info)
{
	const int	now_pipe = (exec_info->pipe_idx + 1) % 2;
	const int	prev_pipe = exec_info->pipe_idx % 2;
	int			fd;

	if (exec_info->pipe_cnt == 2)
	{
		if (dup2(exec_info->pipe[prev_pipe][0], STDIN_FILENO) == -1)
			return (FALSE);
		if (dup2(exec_info->pipe[now_pipe][1], STDOUT_FILENO) == -1)
			return (FALSE);
	}
	else if (exec_info->pipe_cnt == 1 \
	&& exec_info->pipe_idx < exec_info->cmd_cnt)
		fd = STDIN_FILENO;
	else if (exec_info->pipe_cnt == 1 && exec_info->pipe_idx == 1)
		fd = STDOUT_FILENO;
	if (dup2(exec_info->pipe[now_pipe][fd], fd) == -1)
		return (FALSE);
	return (TRUE);
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
