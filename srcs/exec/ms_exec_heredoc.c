/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:08:10 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/04 19:37:56 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ms_minishell.h"
#include <readline/readline.h>

t_bool	ms_exec_io_here(t_exec *exec_info)
{
	const int	seq = exec_info->heredoc_seq;
	char		*filename;

	filename = ms_get_heredoc_filename(seq);
	if (!filename)
	{
		ms_puterror_cmd(NULL, "malloc");
		return (FALSE);
	}
	if (exec_info->fd[0] != -1)
	{
		if (close(exec_info->fd[0]) == -1)
			ms_puterror_cmd(NULL, "close");
		exec_info->fd[0] = -1;
	}
	if (exec_info->heredoc_fd[seq] == -1)
	{
		exec_info->heredoc_fd[seq] = open(filename, O_RDONLY);
		if (exec_info->heredoc_fd[seq] == -1)
		{
			ms_puterror_cmd(NULL, "open");
			return (FALSE);
		}
	}
	exec_info->heredoc_seq++;
	free(filename);
	return (TRUE);
}
