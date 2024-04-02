/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:08:10 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/02 19:54:35 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ms_error.h"
#include "ms_env.h"
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
		write(exec_info->fd[1], line, ft_strlen(line));
		write(exec_info->fd[1], "\n", 1);
		free(line);
	}
	dup2 (exec_info->fd[1], STDIN_FILENO);
	return (TRUE);
}

static t_bool	set_here_fd(t_exec *exec_info)
{
	if (exec_info->fd[1] != -1)
	{
		if (close(exec_info->fd[1]) == -1)
		{
			write(2, "close\n", 6);
			return (FALSE);
		}
	}
	exec_info->fd[1] = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec_info->fd[1] == -1)
	{
		write(2, "No such file or directory : .heredoc\n", 36);
		exec_info->exit_code = 1;
		return (FALSE);
	}
	return (TRUE);
}
