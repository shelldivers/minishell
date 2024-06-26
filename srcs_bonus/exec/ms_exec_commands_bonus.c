/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_commands_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:06:40 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 20:29:36 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_builtin_bonus.h"
#include "ms_error_bonus.h"
#include "ms_exec_bonus.h"
#include "ms_expand_bonus.h"
#include "ms_signal_bonus.h"
#include <unistd.h>

void	ms_exec_words(t_exec *exec_info, t_env **env)
{
	char	**words;

	words = NULL;
	exec_info->cmd_cnt++;
	if (exec_info->words)
		words = ms_expansion(exec_info->words, *env);
	if (exec_info->pipe_idx != 0)
	{
		exec_info->execed_cmd_cnt++;
		ms_exec_commands_fork(exec_info, env, words);
	}
	else if (!ms_exec_is_builtin(exec_info, env, words))
	{
		exec_info->execed_cmd_cnt++;
		ms_exec_non_builtin(exec_info, env, words);
	}
	ms_clear_sec_dimentional(words);
	words = NULL;
	ms_close_stdin(exec_info);
	ms_close_stdout(exec_info);
	ms_reset_exec_info(exec_info);
}

t_bool	ms_exec_is_builtin(t_exec *exec_info, t_env **env, char **words)
{
	if (!words || !words[0])
		return (FALSE);
	if (ft_strcmp(words[0], "echo") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_echo));
	if (ft_strcmp(words[0], "cd") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_cd));
	if (ft_strcmp(words[0], "pwd") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_pwd));
	if (ft_strcmp(words[0], "export") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_export));
	if (ft_strcmp(words[0], "unset") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_unset));
	if (ft_strcmp(words[0], "env") == 0)
		return (ms_exec_builtin(exec_info, env, words, ms_env));
	if (ft_strcmp(words[0], "exit") == 0)
		return (ms_exec_builtin(exec_info, env, words, NULL));
	return (FALSE);
}

t_bool	ms_exec_builtin(t_exec *exec_info, t_env **env, \
char **words, int (f)(int, char **, t_env **))
{
	const int	argc = ms_words_size(words);

	(void)exec_info;
	if (!f)
		ms_exit(argc, words, env, 0);
	else
		g_exit = f(argc, words, env);
	return (TRUE);
}

void	ms_exec_non_builtin(t_exec *exec_info, t_env **env, char **words)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
		ms_puterror_fork();
	if (pid == 0)
	{
		if (!words)
			exit(g_exit);
		else if (!words[0])
			exit(0);
		ms_set_signal_default();
		ms_add_path(words, env);
		execve(words[0], words, ms_env_serialize(*env));
		ms_puterror_no_command(words[0]);
		exit(127);
	}
	else
	{
		ms_set_signal_ignore();
		exec_info->pid = pid;
	}
}
