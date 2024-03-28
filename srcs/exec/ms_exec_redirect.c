/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:08:04 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/28 15:50:19 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ms_env.h"
#include "ms_builtin.h"
#include "minishell.h"

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
		perror("minishell");
		exec_info->exit_code = 1;
		return (FALSE);
	}
	if (dup2(exec_info->fd[1], STDOUT_FILENO) == -1)
	{
		perror("minishell");
		exec_info->exit_code = 1;
		return (FALSE);
	}
	return (TRUE);
}

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
		perror("minishell");
		exec_info->exit_code = 1;
		return (FALSE);
	}
	if (dup2(exec_info->fd[1], STDOUT_FILENO) == -1)
	{
		perror("minishell");
		exec_info->exit_code = 1;
		return (FALSE);
	}
	return (TRUE);
}

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
		exec_info->exit_code = 1;
		return (FALSE);
	}
	if (dup2(exec_info->fd[0], STDIN_FILENO) == -1)
	{
		perror("minishell");
		exec_info->exit_code = 1;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	ms_exec_io_file(t_ast *ast, t_exec *exec_info, t_env **env)
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
