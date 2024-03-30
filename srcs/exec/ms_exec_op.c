/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:07:43 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/30 18:29:13 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ms_env.h"
#include "ms_builtin.h"
#include "minishell.h"

// t_bool	ms_exec_subshell(t_ast *ast, t_exec *exec_info, t_env **env)
// {
// 	int		pid;
// 	int		status;
// 	t_ast	*subshell;
// 	size_t	curtok;

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("minishell");
// 		exec_info->exit_code = 1;
// 		return (FALSE);
// 	}
// 	if (pid == 0)
// 	{
// 		subshell = ms_new_ast(ast->token + 1, ast->token_size - 1);
// 		curtok = ms_parser(&subshell, ast->token + 1, ast->token_size - 1);
// 		if (curtok != ast->token_size - 1)
// 		{
// 			ms_clear_ast(ast);
// 			exit(1);
// 		}
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		exec_info->exit_code = WEXITSTATUS(status);
// 	}
// 	return (TRUE);
// }

t_bool	ms_exec_based_on_op(t_ast *ast, t_exec *exec_info, t_env **env)
{
	// if (ast->op == OPAND_IF || ast->op == OPOR_IF)
	// {
	// 	ms_exec_words(exec_info, env);
	// 	if (ast->op == OPAND_IF && exec_info->exit_code != 0)
	// 		return (FALSE);
	// 	else if (ast->op == OPOR_IF && exec_info->exit_code == 0)
	// 		return (FALSE);
	// }
	// else if (ast->op == OPIO_HERE)
	// 	return (ms_exec_io_here(ast, exec_info, env));
	// else if (ast->op == OPSUBSHELL)
		// return (ms_exec_subshell(ast, exec_info, env));
	if (ast->op == OPPIPE)
	{
		ms_exec_pipe(ast, exec_info, env);
		ms_exec_words(exec_info, env);
	}
	else if (ast->op == OPIO_FILE)
		return (ms_exec_io_file(ast, exec_info, env));
	else if (ast->op == OPCMD_WORD)
		return (ms_create_words(exec_info, ast->token[0]->value));
	else if (ast->op == OPWORD)
		return (ms_add_word(exec_info, ast->token[0]->value));
	return (TRUE);
}
