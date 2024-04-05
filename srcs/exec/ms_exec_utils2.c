/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:25:35 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 15:44:58 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "ms_minishell.h"

static int	w_int(int x);

int	wifexit(int x)
{
	return ((w_int(x) & 0177) == 0);
}

int	wexitstatus(int x)
{
	return ((w_int(x) >> 8) & 0x000000ff);
}

static int	w_int(int x)
{
	return (*(int *)&(x));
}

void	dup2_fd(t_exec *exec_info)
{
	const int	seq = exec_info->heredoc_seq - 1;

	if (exec_info->fd[0] != -1)
	{
		if (dup2(exec_info->fd[0], STDIN_FILENO) == -1)
			ms_puterror_cmd(NULL, "dup2");
	}
	else if (exec_info->fd[0] == -1 && seq >= 0 \
	&& exec_info->heredoc_fd[seq] > 0)
	{
		if (dup2(exec_info->heredoc_fd[seq], STDIN_FILENO) == -1)
			ft_dprintf(2, "damn");
	}
	if (exec_info->fd[1] != -1)
		if (dup2(exec_info->fd[1], STDOUT_FILENO) == -1)
			ms_puterror_cmd(NULL, "dup2");
}
