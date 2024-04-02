/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:31:49 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/02 19:49:57 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_exec.h"

void	ms_exec(t_ast *ast, t_env **env)
{
	int		pid;
	t_exec	*exec_info;

	if (!ast)
		return ;
	exec_info = ms_new_exec_info(env);
	if (!exec_info)
		ms_env_clear(env);
	ms_exec_in_order(ast, exec_info, env);
	if (exec_info->words)
		ms_exec_words(exec_info, env);
	ms_wait_child_process(exec_info);
	reset_exec_info(exec_info);
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
	if (!ms_exec_in_order(left, exec_info, env))
		return (FALSE);
	if (ast->op != OPNONE)
	{
		status = ms_exec_based_on_op(ast, exec_info, env);
		if (status == -1)
			return (TRUE);
		else if (status == 0)
			return (FALSE);
	}
	if (!ms_exec_in_order(right, exec_info, env))
		return (FALSE);
	return (TRUE);
}

int	ms_exec_based_on_op(t_ast *ast, t_exec *exec_info, t_env **env)
{
	if (ast->op == OPAND_IF || ast->op == OPOR_IF)
	{
		ms_exec_words(exec_info, env);
		ms_wait_child_process(exec_info);
		if (ast->op == OPAND_IF && exec_info->exit_code != 0)
			return (-1);
		else if (ast->op == OPOR_IF && exec_info->exit_code == 0)
			return (-1);
	}
	else if (ast->op == OPPIPE)
	{
		ms_exec_pipe(ast, exec_info, env);
		ms_exec_words(exec_info, env);
	}
	else if (ast->op == OPIO_FILE)
		return (ms_exec_io_file(ast, exec_info));
	else if (ast->op == OPWORD)
		return (ms_add_word(exec_info, ast->token[0]->value));
	else if (ast->op == OPIO_HERE)
		return (ms_exec_io_here(exec_info, ast->token[1]->value));
	return (TRUE);
}
