/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:08:10 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/03 18:15:16 by jiwojung         ###   ########.fr       */
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
	char	*line;

	if (!set_here_fd(exec_info))
		return (FALSE);
	while (1)
	{
		line = readline("miniheredoc> ");
		if (line == 0)
			break ;
		if (ft_strcmp(line, here_end) == 0)
		{
			free(line);
			break ;
		}
		write(exec_info->fd[0], line, ft_strlen(line));
		write(exec_info->fd[0], "\n", 1);
		free(line);
	}
	return (TRUE);
}

static t_bool	set_here_fd(t_exec *exec_info)
{
	if (exec_info->fd[0] != -1)
		close(exec_info->fd[0]);
	exec_info->fd[0] = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (TRUE);
}
