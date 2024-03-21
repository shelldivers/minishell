/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:31:49 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/21 15:02:18 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

void	clear_sec_demention(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	init_exec_info(t_exec *exec_info)
{
	exec_info->words = NULL;
	exec_info->exit_code = 0;
	exec_info->pipe[0][0] = 0;
	exec_info->pipe[0][1] = 0;
	exec_info->pipe[1][0] = 0;
	exec_info->pipe[1][1] = 0;
	exec_info->pipe_cnt = 0;
}



void	ms_exec_cmd(t_ast *ast, t_exec *exec_info)
{
	if (!ast)
		return ;
	ms_exec_cmd(ast->left, exec_info);
	if (ast->op != OPNONE)
	{
		// exec_based_on_op(ast->op, exec_info);
	}
	ms_exec_cmd(ast->right, exec_info);
}

void	set_origin_fd(int *origin_fd)
{
	origin_fd[0] = dup(STDIN_FILENO);
	origin_fd[1] = dup(STDOUT_FILENO);
	origin_fd[2] = dup(STDERR_FILENO);
}

void	ms_exec(t_ast *ast)
{
	t_exec	exec_info;
	int		origin_fd[3];

	init_exec_info(&exec_info);
	set_origin_fd(origin_fd);
	ms_exec_cmd(ast, &exec_info);
}
