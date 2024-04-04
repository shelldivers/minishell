/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:08:10 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/04 10:48:24 by jiwojung         ###   ########.fr       */
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

t_bool	ms_exec_io_here(t_exec *exec_info)
{
	int			cnt;
	t_heredoc	*heredoc;

	cnt = 1;
	heredoc = exec_info->heredoc;
	while (cnt < exec_info->heredoc_cnt)
	{
		heredoc = heredoc->next;
		cnt++;
	}
	dup2(heredoc->fd, STDIN_FILENO);
	exec_info->heredoc_cnt++;
	return (TRUE);
}

void	ms_add_back_heredoc(t_heredoc **heredoc, t_heredoc *new_heredoc)
{
	t_heredoc	*curr;

	if (!heredoc || !new_heredoc)
		return ;
	if (!*heredoc)
	{
		*heredoc = new_heredoc;
		return ;
	}
	curr = *heredoc;
	while (curr->next)
		curr = curr->next;
	curr->next = new_heredoc;
}

t_heredoc	*ms_new_heredoc(char *filename, char *here_end)
{
	char		*line;
	int			fd;
	t_heredoc	*heredoc;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->filename = filename;
	heredoc->fd = fd;
	heredoc->next = NULL;
	while (1)
	{
		line = readline("minidoc> ");
		if (!line)
			break ;
		else if (!ft_strcmp(line, here_end))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (heredoc);
}

t_heredoc	*ms_remove_heredoc_head(t_heredoc *heredoc)
{
	t_heredoc	*next;

	if (!heredoc)
		return (NULL);
	next = heredoc->next;
	free(heredoc->filename);
	close(heredoc->fd);
	free(heredoc);
	heredoc = NULL;
	return (next);
}
