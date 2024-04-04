/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_init_clear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:23:38 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/04 10:16:29 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ms_exec.h"

void	ms_init_exec_info(t_exec *exec_info)
{
	exec_info->words = NULL;
	exec_info->words_size = 0;
	exec_info->origin_fd[0] = dup(STDIN_FILENO);
	exec_info->origin_fd[1] = dup(STDOUT_FILENO);
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
	exec_info->execed_cmd_cnt = 0;
	exec_info->heredoc = NULL;
	exec_info->heredoc_cnt = 0;
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
	while (exec_info->heredoc_cnt)
	{
		if (access(exec_info->heredoc->filename, F_OK) == 0)
			unlink(exec_info->heredoc->filename);
		exec_info->heredoc = ms_remove_heredoc_head(exec_info->heredoc);
		exec_info->heredoc_cnt--;
	}
}