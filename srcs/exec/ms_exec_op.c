/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:07:43 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/26 18:46:47 by jiwojung         ###   ########.fr       */
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
	const char	*redirect = ast->token[0];
	const char	*filename = ast->token[1];

	if (ft_strcmp(redirect, ">") == 0)
		return (ms_exec_io_file_write(exec_info, filename));
	else if (ft_strcmp(redirect, ">>") == 0)
		return (ms_exec_io_file_append(exec_info, filename));
	else if (ft_strcmp(redirect, "<") == 0)
		return (ms_exec_io_file_read(exec_info, filename));
	return (FALSE);
}

t_bool	ms_exec_subshell(t_ast *ast, t_exec *exec_info, t_env **env)
{
	
}

t_bool	ms_exec_based_on_op(t_ast *ast, t_exec *exec_info, t_env **env)
{
	if (ast->op == OPAND_IF || ast->op == OPOR_IF)
	{
		ms_exec_words(exec_info, env);
		if (ast->op == OPAND_IF && exec_info->exit_code != 0)
			return (FALSE);
		else if (ast->op == OPOR_IF && exec_info->exit_code == 0)
			return (FALSE);
	}
	else if (ast->op == OPPIPE)
	{
		ms_exec_pipe(ast, exec_info, env);
		ms_exec_words(exec_info, env);
	}
	else if (ast->op == OPIO_FILE)
		return (ms_exec_io_file(ast, exec_info, env));
	else if (ast->op == OPIO_HERE)
		return (ms_exec_io_here(ast, exec_info, env));
	else if (ast->op == OPSUBSHELL)
		return (ms_exec_subshell(ast, exec_info, env));
	else if (ast->op == OPCMD_WORD)
		return (ms_create_words(exec_info, ast->token[0]));
	else if (ast->op == OPWORD)
		return (ms_add_word(exec_info, ast->token[0]));
	return (TRUE);
}
