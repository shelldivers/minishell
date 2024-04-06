/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:06:40 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 15:37:45 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_builtin.h"
#include "ms_error.h"
#include "ms_exec.h"
#include "ms_expand.h"
#include <stdio.h>
#include <unistd.h>

void	ms_exec_words(t_exec *exec_info, t_env **env)
{
	char	**words;

	exec_info->cmd_cnt++;
	if (exec_info->words)
	{
		words = ms_expansion(exec_info->words, *env, exec_info->exit_code);
		exec_info->execed_cmd_cnt++;
		if (!ms_exec_is_builtin(exec_info, env, words))
			ms_exec_non_builtin(exec_info, env, words);
		ms_clear_sec_dimentional(words);
		free(exec_info->words);
		exec_info->words = NULL;
		words = NULL;
	}
	ms_reset_exec_info(exec_info);
}

t_bool	ms_exec_is_builtin(t_exec *exec_info, t_env **env, char **words)
{
	char	*word;

	word = words[0];
	if (!words || !word)
		return (FALSE);
	if (ft_strcmp(word, "echo") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_echo));
	if (ft_strcmp(word, "cd") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_cd));
	if (ft_strcmp(word, "pwd") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_pwd));
	if (ft_strcmp(word, "export") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_export));
	if (ft_strcmp(word, "unset") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_unset));
	if (ft_strcmp(word, "env") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_env));
	if (ft_strcmp(word, "exit") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_exit));
	return (FALSE);
}

t_bool	ms_exec_builtin(t_exec *exec_info, t_env **env, \
char **words, int (f)(int, char **, t_env **))
{
	const size_t	argc = ms_words_size(words);

	ms_dup_based_on_pipe_idx(exec_info);
	exec_info->exit_code = f(argc, words, env);
	ms_close_parent_pipe(exec_info);
	return (TRUE);
}

void	ms_exec_non_builtin(t_exec *exec_info, t_env **env, char **words)
{
	int			pid;

	pid = fork();
	if (pid == -1)
	{
		ms_puterror_fork();
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		ms_add_path(words, env);
		ms_dup_based_on_pipe_idx(exec_info);
		ms_close_all_fd(exec_info);
		execve(words[0], words, ms_env_serialize(*env));
		ms_puterror_no_command(words[0]);
		exit(EXIT_FAILURE);
	}
	else
		ms_close_parent_pipe(exec_info);
}
