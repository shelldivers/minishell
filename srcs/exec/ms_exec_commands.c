/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:06:40 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/03 17:39:28 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "ms_env.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ms_expand.h"

void	ms_exec_words(t_exec *exec_info, t_env **env)
{
	char	**words;

	exec_info->cmd_cnt++;
	if (exec_info->words)
	{
		words = ms_expansion(exec_info->words, *env, exec_info->exit_code);
		exec_info->execed_cmd_cnt++;
		if (ms_exec_is_builtin(words))
			ms_exec_builtin(exec_info, env, words);
		else
			ms_exec_non_builtin(exec_info, env, words);
		ms_clear_sec_dimentional(words);
		free(exec_info->words);
		exec_info->words = NULL;
		words = NULL;
	}
	ms_reset_exec_info(exec_info);
}

t_bool	ms_exec_is_builtin(char **words)
{
	char	*word;

	word = words[0];
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

void	ms_exec_builtin(t_exec *exec_info, t_env **env, char **words)
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
		ms_exec_builtin2(exec_info, env, words);
		exit(exec_info->exit_code);
	}
	else
	{
		ms_close_parent_pipe(exec_info);
	}
}

void	ms_exec_builtin2(t_exec *exec_info, t_env **env, char **words)
{
	const size_t	argc = ms_words_size(words);

	if (ft_strcmp(words[0], "echo") == 0)
		exec_info->exit_code = ms_echo(argc, words, env);
	else if (ft_strcmp(words[0], "cd") == 0)
		exec_info->exit_code = ms_cd(argc, words, env);
	else if (ft_strcmp(words[0], "pwd") == 0)
		exec_info->exit_code = ms_pwd(argc, words, env);
	else if (ft_strcmp(words[0], "export") == 0)
		exec_info->exit_code = ms_export(argc, words, env);
	else if (ft_strcmp(words[0], "unset") == 0)
		exec_info->exit_code = ms_unset(argc, words, env);
	else if (ft_strcmp(words[0], "env") == 0)
		exec_info->exit_code = ms_env(argc, words, env);
	else if (ft_strcmp(words[0], "exit") == 0)
		exec_info->exit_code = ms_exit(argc, words, env);
}

void	ms_exec_non_builtin(t_exec *exec_info, t_env **env, char **words)
{
	int			pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, "fork in nonbuiltin\n", 19);
		return ;
	}
	if (pid == 0)
	{
		if (!ms_add_path(words, env))
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
