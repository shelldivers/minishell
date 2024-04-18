/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:08:10 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 16:35:03 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_error.h"
#include "ms_exec.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	ms_close_stdin(exec_info);
	if (exec_info->heredoc_fd[seq] == CLOSED)
	{
		if (access(filename, F_OK) == FAILED)
		{
			free(filename);
			return (TRUE);
		}
		exec_info->heredoc_fd[seq] = open(filename, O_RDONLY);
		if (exec_info->heredoc_fd[seq] == FAILED)
			ms_puterror_cmd(NULL, "open");
	}
	exec_info->heredoc_seq += 1;
	free(filename);
	return (TRUE);
}
