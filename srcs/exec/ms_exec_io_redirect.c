/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_io_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:08:04 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/04 21:56:38 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ms_minishell.h"
#include <readline/readline.h>

t_bool	ms_exec_io_file(t_ast *ast, t_exec *exec_info)
{
	const char	*redirect = ast->token[0]->value;
	const char	*filename = ast->token[1]->value;

	if (ft_strcmp(redirect, ">") == 0)
		return (ms_exec_io_file_write(exec_info, filename));
	else if (ft_strcmp(redirect, ">>") == 0)
		return (ms_exec_io_file_append(exec_info, filename));
	else if (ft_strcmp(redirect, "<") == 0)
		return (ms_exec_io_file_read(exec_info, filename));
	return (FALSE);
}

// error handling in this function
t_bool	ms_exec_io_file_write(t_exec *exec_info, const char *filename)
{
	if (exec_info->fd[1] != -1)
	{
		close(exec_info->fd[1]);
		exec_info->fd[1] = -1;
	}
	exec_info->fd[1] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec_info->fd[1] == -1)
	{
		ms_puterror_cmd(NULL, "filename");
		exec_info->exit_code = 1;
		return (FALSE);
	}
	return (TRUE);
}

// error handling in this function
t_bool	ms_exec_io_file_append(t_exec *exec_info, const char *filename)
{
	if (exec_info->fd[1] != -1)
	{
		close(exec_info->fd[1]);
		exec_info->fd[1] = -1;
	}
	exec_info->fd[1] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (exec_info->fd[1] == -1)
	{
		ms_puterror_cmd(NULL, "filename");
		exec_info->exit_code = 1;
		return (FALSE);
	}
	return (TRUE);
}

// error handling in this function
t_bool	ms_exec_io_file_read(t_exec *exec_info, const char *filename)
{
	if (exec_info->fd[0] != -1)
	{
		close(exec_info->fd[0]);
		exec_info->fd[0] = -1;
	}
	exec_info->fd[0] = open(filename, O_RDONLY);
	if (exec_info->fd[0] == -1)
	{
		ms_puterror_cmd(NULL, "filename");
		exec_info->exit_code = 1;
		return (FALSE);
	}
	return (TRUE);
}

void	dup2_fd(t_exec *exec_info)
{
	const int	seq = exec_info->heredoc_seq - 1;

	if (exec_info->fd[0] != -1)
	{
		if (dup2(exec_info->fd[0], STDIN_FILENO) == -1)
			ms_puterror_cmd(NULL, "dup2");
	}
	else if (exec_info->fd[0] == -1 && exec_info->heredoc_fd[seq] > 0)
	{
		if (dup2(exec_info->heredoc_fd[seq], STDIN_FILENO) == -1)
			ms_puterror_cmd(NULL, "dup2");
	}
	if (exec_info->fd[1] != -1)
		if (dup2(exec_info->fd[1], STDOUT_FILENO) == -1)
			ms_puterror_cmd(NULL, "dup2");
}
