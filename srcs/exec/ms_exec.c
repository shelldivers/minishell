/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:31:49 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/21 17:13:12 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

void	ms_init_exec_info(t_exec *exec_info)
{
	exec_info->words = NULL;
	exec_info->exit_code = 0;
	exec_info->fd[0] = 0;
	exec_info->fd[1] = 0;
	exec_info->pipe[0][0] = 0;
	exec_info->pipe[0][1] = 0;
	exec_info->pipe[1][0] = 0;
	exec_info->pipe[1][1] = 0;
	exec_info->pipe_cnt = 0;
}

void	ms_exec_based_on_op(t_ast *ast, t_exec *exec_info)
{
	if (ast->op == OPAND_IF)
		if (exec_info->exit_code == 0)
			ms_exec_if(ast, exec_info);
	else if (ast->op == OPOR_IF)
		ms_exec_if(ast, exec_info);
	else if (ast->op == OPPIPE)
		ms_exec_pipe(ast, exec_info);
	else if (ast->op == OPSUBSHELL)
		ms_exec_subshell(ast, exec_info);
	else if (ast->op == OPIO_FILE)
		ms_exec_io_file(ast, exec_info);
	else if (ast->op == OPIO_HERE)
		ms_exec_io_here(ast, exec_info);
	else if (ast->op == OPCMD_WORD)
		ms_exec_cmd_word(ast, exec_info);
	else if (ast->op == OPWORD)
		ms_exec_word(ast, exec_info);
}

void	ms_exec_post_order(t_ast *ast, t_exec *exec_info)
{
	if (!ast)
		return ;
	ms_exec_post_order(ast->left, exec_info);
	ms_exec_post_order(ast->right, exec_info);
	if (ast->op != OPNONE)
	{
		ms_exec_based_on_op(ast, exec_info);
	}
}

void	ms_exec(t_ast *ast)
{
	t_exec	exec_info;

	ms_init_exec_info(&exec_info);
	ms_exec_post_order(ast, &exec_info);
}
