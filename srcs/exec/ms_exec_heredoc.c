/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:08:10 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/03 21:09:24 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ms_error.h"
#include "ms_exec.h"
#include <readline/readline.h>

static t_bool	set_here_fd(t_exec *exec_info);

t_bool	ms_exec_io_here(t_exec *exec_info, const char *here_end)
{
	t_heredoc	*heredoc;

	heredoc = exec_info->heredoc;
	dup2(heredoc->fd, STDIN_FILENO);
}

static t_bool	set_here_fd(t_exec *exec_info)
{
	
}
