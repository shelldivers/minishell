/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_commands_fork.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:37:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/07 21:29:20 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_builtin.h"
#include "ms_error.h"
#include "ms_exec.h"
#include "ms_expand.h"
#include "ms_signal.h"
#include <unistd.h>

void	ms_exec_commands_fork(t_exec *exec_info, t_env **env, char **words)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ms_puterror_fork();
	if (pid == 0)
	{
		if (!words || !words[0])
			exit(0);
		ms_set_signal_default();
		ms_dup_pipe(exec_info);
		ms_exec_is_builtin_fork(env, words);
		ms_add_path(words, env);
		execve(words[0], words, ms_env_serialize(*env));
		ms_puterror_no_command(words[0]);
		exit(127);
	}
	else
	{
		ms_close_pipe(exec_info);
		exec_info->pid = pid;
	}
}

void	ms_exec_is_builtin_fork(t_env **env, char **words)
{
	if (!words || !words[0])
		return ;
	if (ft_strcmp(words[0], "echo") == 0)
		ms_exec_builtin_fork(env, words, ms_echo);
	if (ft_strcmp(words[0], "cd") == 0)
		ms_exec_builtin_fork(env, words, ms_cd);
	if (ft_strcmp(words[0], "pwd") == 0)
		ms_exec_builtin_fork(env, words, ms_pwd);
	if (ft_strcmp(words[0], "export") == 0)
		ms_exec_builtin_fork(env, words, ms_export);
	if (ft_strcmp(words[0], "unset") == 0)
		ms_exec_builtin_fork(env, words, ms_unset);
	if (ft_strcmp(words[0], "env") == 0)
		ms_exec_builtin_fork(env, words, ms_env);
	if (ft_strcmp(words[0], "exit") == 0)
		ms_exec_builtin_fork(env, words, ms_exit);
}

void	ms_exec_builtin_fork(t_env **env, \
char **words, int (f)(int, char **, t_env **))
{
	const int	argc = ms_words_size(words);

	g_exit = f(argc, words, env);
	exit (g_exit);
}
