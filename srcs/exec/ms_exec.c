/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:31:49 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/28 20:44:02 by jiwojung         ###   ########.fr       */
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

void	wait_child_process(t_exec *exec_info)
{
	int	i;

	i = 0;
	while (i < exec_info->cmd_cnt)
	{
		waitpid(-1, &exec_info->exit_code, 0);
		i++;
	}
}

t_exec	*ms_new_exec_info(t_env **env)
{
	t_exec	*exec_info;

	exec_info = (t_exec *)malloc(sizeof(t_exec));
	if (!exec_info)
	{
		ms_puterror_cmd(*env, "malloc");
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
	exec_info->pipe_idx = 0;
	exec_info->pipe_cnt = 0;
	exec_info->exit_code = 0;
	exec_info->cmd_cnt = 0;
	return (exec_info);
}

void	ms_exec_in_order(t_ast *ast, t_exec *exec_info, t_env **env)
{
	t_ast	*left;
	t_ast	*right;

	if (!ast)
		return ;
	left = ast->left;
	right = ast->right;
	ms_exec_in_order(left, exec_info, env);
	if (ast->op != OPNONE)
		if (!ms_exec_based_on_op(ast, exec_info, env))
			return ;
	ms_exec_in_order(right, exec_info, env);
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
	ms_exec_in_order(ast, exec_info, env);
	if (exec_info->words || !ms_exec_is_builtin(exec_info))
		ms_exec_words(exec_info, env);
	wait_child_process(exec_info);
	free (exec_info->words);
	exec_info->words = NULL;
	free (exec_info);
	exec_info = NULL;
}
