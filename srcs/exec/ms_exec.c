/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:31:49 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 16:27:17 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_signal.h"
#include "ms_exec.h"

void	ms_exec(t_ast *ast, t_env **env)
{
	t_exec	*exec_info;

	if (!ast)
		return ;
	exec_info = ms_new_exec_info(env);
	if (!exec_info)
		ms_env_clear(env);
	if (ms_max_heredoc(ast->token) && !ms_exec_heredoc_before(ast))
	{
		ms_reset_exec_info(exec_info);
		ms_clear_heredoc(exec_info);
		return ;
	}
	ms_exec_in_order(ast, exec_info, env);
	dup2_fd(exec_info);
	ms_exec_words(exec_info, env);
	ms_after_exec(exec_info);
}

void	ms_after_exec(t_exec *exec_info)
{
	if (exec_info->execed_cmd_cnt)
		ms_wait_child_process(exec_info);
	ms_reset_exec_info(exec_info);
	ms_reset_io(exec_info);
	ms_close_all_fd(exec_info);
	ms_clear_heredoc(exec_info);
	free(exec_info);
}

t_bool	ms_exec_in_order(t_ast *ast, t_exec *exec_info, t_env **env)
{
	t_ast	*left;
	t_ast	*right;
	int		status;

	if (!ast)
		return (TRUE);
	left = ast->left;
	right = ast->right;
	if (!ms_exec_in_order(left, exec_info, env)
		&& ast->op != OPAND_IF && ast->op != OPOR_IF && ast->op != OPPIPE)
		return (FALSE);
	if (ast->op != OPNONE)
	{
		status = ms_exec_based_on_op(ast, exec_info, env);
		if (status == FAILED)
			return (TRUE);
		else if (status == FALSE)
			return (FALSE);
	}
	if (!ms_exec_in_order(right, exec_info, env)
		&& ast->op != OPAND_IF && ast->op != OPOR_IF && ast->op != OPPIPE)
		return (FALSE);
	return (TRUE);
}

int	ms_exec_based_on_op(t_ast *ast, t_exec *exec_info, t_env **env)
{
	if (ast->op == OPAND_IF || ast->op == OPOR_IF)
	{
		dup2_fd(exec_info);
		ms_exec_words(exec_info, env);
		ms_wait_child_process(exec_info);
		ms_reset_io(exec_info);
		if ((ast->op == OPAND_IF && g_exit != 0)
			|| (ast->op == OPOR_IF && g_exit == 0))
			return (FAILED);
	}
	else if (ast->op == OPPIPE)
	{
		dup2_fd(exec_info);
		ms_exec_pipe(exec_info);
		ms_exec_words(exec_info, env);
		ms_reset_io(exec_info);
	}
	else if (ast->op == OPIO_FILE)
		return (ms_exec_io_file(ast, exec_info, env));
	else if (ast->op == OPWORD)
		return (ms_add_word(exec_info, ast->token[0]->value));
	else if (ast->op == OPIO_HERE)
		return (ms_exec_io_here(exec_info));
	return (TRUE);
}
