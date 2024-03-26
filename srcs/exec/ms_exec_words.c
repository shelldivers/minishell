/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:06:40 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/26 15:55:49 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "ms_env.h"
#include "ms_builtin.h"
#include "minishell.h"

void	ms_exec_builtin(t_exec *exec_info, t_env **env)
{
	const int	argc = exec_info->words_size;
	const char	**argv = exec_info->words;

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

t_bool	ms_exec_is_builtin(t_exec *exec_info)
{
	const char	*word = exec_info->words[0];

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

t_bool	ms_exec_non_builtin(t_exec *exec_info, t_env **env)
{
	const char	**words = exec_info->words;
	int			pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (TRUE);
	}
	if (pid == 0)
	{
		if (execve(words[0], words, ms_env_serialize(env)) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &exec_info->exit_code, 0);
		if (WIFEXITED(exec_info->exit_code))
			exec_info->exit_code = WEXITSTATUS(exec_info->exit_code);
	}
}

t_bool	ms_exec_words(t_exec *exec_info, t_env **env)
{
	const char	**words = exec_info->words;

	if (words)
	{
		if (ms_exec_is_builtin(words[0]))
			ms_exec_builtin(exec_info, env);
		else
		{
			ms_add_path(exec_info, env);
			ms_exec_non_builtin(exec_info, env);
		}
	}
	return (FALSE);
}
