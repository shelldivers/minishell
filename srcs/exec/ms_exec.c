/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:31:49 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/26 18:45:01 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "ms_env.h"
#include "ms_builtin.h"
#include "minishell.h"
#include "ms_error.h"
#include "sys/errno.h"

t_exec	*ms_new_exec_info(t_env **env)
{
	t_exec	*exec_info;

	exec_info = (t_exec *)malloc(sizeof(t_exec));
	if (!exec_info)
	{
		ms_puterror_cmd(env, "malloc");
		return (NULL);
	}
	exec_info->words = NULL;
	exec_info->words_size = 0;
	exec_info->fd[0] = -1;
	exec_info->fd[1] = -1;
	exec_info->pipe[0][0] = -1;
	exec_info->pipe[0][1] = -1;
	exec_info->pipe[1][0] = -1;
	exec_info->pipe[1][1] = -1;
	exec_info->pipe_cnt = 0;
	exec_info->exit_code = 0;
	return (exec_info);
}

t_bool	ms_exec_in_order(t_ast *ast, t_exec *exec_info, t_env **env)
{
	t_ast	*left;
	t_ast	*right;

	if (!ast)
		return ;
	left = ast->left;
	right = ast->right;
	if (!ms_exec_in_order(left, exec_info, env))
		return (FALSE);
	if (ast->op != OPNONE)
		if (!ms_exec_based_on_op(ast, exec_info, env))
			return (FALSE);
	if (!ms_exec_in_order(right, exec_info, env))
		return (FALSE);
	return (TRUE);
}

void	ms_exec(t_ast *ast, t_env **env)
{
	int		pid;
	t_exec	*exec_info;

	if (!ast)
		return ;
	exec_info = ms_new_exec_info(env);
	if (!exec_info)
		ms_env_clear(env);
	if (!ms_exec_in_order(ast, exec_info, env))
	{
		ms_clear_exec_info(exec_info);
	}
	if (exec_info->words || !ms_exec_is_builtin(exec_info->words[0]))
	{
		ms_exec_words(exec_info, env);
		ms_clear_sec_dimentional(exec_info->words);
		exec_info->words = NULL;
	}
}
