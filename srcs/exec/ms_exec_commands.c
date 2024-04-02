/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:06:40 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/02 20:14:33 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ms_env.h"
#include "ms_builtin.h"
#include "ms_exec.h"

void	ms_exec_words(t_exec *exec_info, t_env **env)
{
	char	**words;

	words = exec_info->words;
	if (words)
	{
		exec_info->cmd_cnt++;
		if (ms_exec_is_builtin(exec_info))
			ms_exec_builtin(exec_info, env);
		else
			ms_exec_non_builtin(exec_info, env);
	}
	reset_exec_info(exec_info);
}

t_bool	ms_exec_is_builtin(t_exec *exec_info)
{
	char	*word;

	word = exec_info->words[0];
	if (ft_strcmp(word, "echo") == 0)
		return (TRUE);
	if (ft_strcmp(word, "cd") == 0)
		return (TRUE);
	if (ft_strcmp(word, "pwd") == 0)
		return (TRUE);
	if (ft_strcmp(word, "export") == 0)
		return (TRUE);
	if (ft_strcmp(word, "unset") == 0)
		return (TRUE);
	if (ft_strcmp(word, "env") == 0)
		return (TRUE);
	if (ft_strcmp(word, "exit") == 0)
		return (TRUE);
	return (FALSE);
}

void	ms_exec_builtin(t_exec *exec_info, t_env **env)
{
	int		pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, "fork in builtin\n", 16);
		return ;
	}
	else if (pid == 0)
	{
		ms_dup_based_on_pipe_idx(exec_info);
		ms_close_all_fd(exec_info);
		ms_exec_builtin2(exec_info, env);
		exit(exec_info->exit_code);
	}
	else
	{
		ms_close_parent_pipe(exec_info);
	}
}

void	ms_exec_builtin2(t_exec *exec_info, t_env **env)
{
	int		argc;
	char	**argv;

	argc = exec_info->words_size;
	argv = exec_info->words;
	if (ft_strcmp(argv[0], "echo") == 0)
		exec_info->exit_code = ms_echo(argc, argv, env);
	else if (ft_strcmp(argv[0], "cd") == 0)
		exec_info->exit_code = ms_cd(argc, argv, env);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		exec_info->exit_code = ms_pwd(argc, argv, env);
	else if (ft_strcmp(argv[0], "export") == 0)
		exec_info->exit_code = ms_export(argc, argv, env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		exec_info->exit_code = ms_unset(argc, argv, env);
	else if (ft_strcmp(argv[0], "env") == 0)
		exec_info->exit_code = ms_env(argc, argv, env);
	else if (ft_strcmp(argv[0], "exit") == 0)
		exec_info->exit_code = ms_exit(argc, argv, env);
}

void	ms_exec_non_builtin(t_exec *exec_info, t_env **env)
{
	char *const	*words = exec_info->words;
	int			pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, "fork in nonbuiltin\n", 19);
		return ;
	}
	if (pid == 0)
	{
		if (!ms_add_path(exec_info, env))
		{
			write(2, "minishell: command not found: ", 30);
			write(2, words[0], ft_strlen(words[0]));
			write(2, "\n", 1);
			exit(3);
		}
		ms_dup_based_on_pipe_idx(exec_info);
		ms_close_all_fd(exec_info);
		execve(words[0], words, ms_env_serialize(*env));
		write(2, "execve in non builtin\n", 22);
		exit(EXIT_FAILURE);
	}
	else
	{
		ms_close_parent_pipe(exec_info);
	}
}
