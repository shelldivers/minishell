/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_init_clear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:23:38 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 11:48:58 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ms_minishell.h"

void	ms_init_exec_info(t_exec *exec_info)
{
	int	i;

	ft_memset(exec_info, 0, sizeof(t_exec));
	exec_info->origin_fd[0] = dup(STDIN_FILENO);
	exec_info->origin_fd[1] = dup(STDOUT_FILENO);
	exec_info->fd[0] = -1;
	exec_info->fd[1] = -1;
	exec_info->pipe[0][0] = -1;
	exec_info->pipe[0][1] = -1;
	exec_info->pipe[1][0] = -1;
	exec_info->pipe[1][1] = -1;
	i = 0;
	while (i < 7)
		exec_info->heredoc_fd[i++] = -1;
}

void	ms_clear_sec_dimentional(char **words)
{
	int	i;

	i = 0;
	if (!words)
		return ;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

void	ms_clear_heredoc(t_exec *exec_info)
{
	char	*filename;
	int		seq;

	seq = exec_info->heredoc_seq - 1;
	while (seq >= 0)
	{
		filename = ms_get_heredoc_filename(seq);
		if (!filename)
		{
			ms_puterror_cmd(NULL, "malloc");
			return ;
		}
		if (access(filename, F_OK) == 0)
			unlink(filename);
		free(filename);
		if (exec_info->heredoc_fd[seq] != -1)
		{
			close(exec_info->heredoc_fd[seq]);
			exec_info->heredoc_fd[seq] = -1;
		}
		seq--;
	}
	exec_info->heredoc_seq = 0;
}

void	ms_reset_exec_info(t_exec *exec_info)
{
	if (exec_info->words)
		free (exec_info->words);
	exec_info->words = NULL;
	exec_info->words_size = 0;
}

void	ms_reset_io(t_exec *exec_info)
{
	if (dup2(exec_info->origin_fd[0], STDIN_FILENO) == -1)
		ms_puterror_cmd(NULL, "dup2");
	if (dup2(exec_info->origin_fd[1], STDOUT_FILENO) == -1)
		ms_puterror_cmd(NULL, "dup2");
}
