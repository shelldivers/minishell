/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:31:49 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/22 17:27:43 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

void	ms_init_exec_info(t_exec *exec_info)
{
	exec_info->words = NULL;
	exec_info->fd[0] = 0;
	exec_info->fd[1] = 0;
	exec_info->pipe[0][0] = 0;
	exec_info->pipe[0][1] = 0;
	exec_info->pipe[1][0] = 0;
	exec_info->pipe[1][1] = 0;
	exec_info->pipe_cnt = 0;
}

void	ms_exec_based_on_op(t_ast *ast, t_exec *exec_info, int *exit_code)
{
	if (ast->op == OPAND_IF)
	{
		if (exit_code == 0)
			ms_exec_if(exec_info);
	}
	else if (ast->op == OPOR_IF)
	{
		if (exit_code != 0)
			ms_exec_if(exec_info);
	}
	else if (ast->op == OPPIPE)
		ms_exec_pipe(exec_info, exit_code);
	else if (ast->op == OPSUBSHELL)
		ms_exec_subshell(ast, exit_code);
	else if (ast->op == OPIO_FILE)
		ms_exec_io_file(ast->token[0]->type, ast->token[1]->value, exec_info);
	else if (ast->op == OPIO_HERE)
		ms_exec_io_here(ast, exec_info);
	else if (ast->op == OPCMD_WORD)
		ms_exec_cmd_word(ast->token[0]->value, exec_info);
	else if (ast->op == OPWORD)
		ms_exec_word(ast->token[0]->value, exec_info);
}

void	ms_exec_post_order(t_ast *ast, t_exec *exec_info, int *exit_code)
{
	if (!ast)
		return ;
	ms_exec_post_order(ast->left, exec_info, exit_code);
	if (ast->op != OPNONE)
	{
		ms_exec_based_on_op(ast, exec_info, exit_code);
	}
	ms_exec_post_order(ast->right, exec_info, exit_code);
}

void	ms_exec(t_ast *ast, int *exit_code)
{
	int		pid;
	t_exec	exec_info;

	ms_init_exec_info(&exec_info);
	ms_exec_post_order(ast, &exec_info, exit_code);
	if (exec_info.words)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			execve(exec_info.words[0], exec_info.words, NULL);
			ms_clear_words(exec_info.words);
		}
	}
}
