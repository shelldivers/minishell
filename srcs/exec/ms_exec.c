/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:31:49 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/25 19:46:49 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "ms_env.h"
#include "minishell.h"

t_exec	*ms_init_exec_info(void)
{
	t_exec	*exec_info;

	exec_info = (t_exec *)malloc(sizeof(t_exec));
	if (!exec_info)
		return (NULL);
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


t_bool	excuting(t_exec *exec_info, t_env **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (FALSE);
	if (pid == 0)
	{
		if (execve(exec_info->words[0], exec_info->words, NULL) == -1)
		{
			ms_clear_words(exec_info->words);
			ms_env_clear(env);
		}
	}
	else
	{
		ms_clear_words(exec_info->words);
		ms_env_clear(env);
	}
	return (TRUE);
}

void	ms_exec(t_ast *ast, char **envp)
{
	int		pid;
	t_env	**env;
	t_exec	*exec_info;

	if (!ast)
		return ;
	env = ms_env_deserialize(envp);
	if (!env)
		printf ("env is NULL\n");
	exec_info = ms_init_exec_info();
	if (!exec_info)
	{
		ms_env_clear(env);
		printf ("exec_info is NULL\n");
	}
	if (!ms_is_builtin(exec_info->words[0]))
		ms_find_path(exec_info->words, *env);
	// ms_exec_in_order(ast, exec_info);
}
