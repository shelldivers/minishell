/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:08:10 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/04 14:55:07 by jiwojung         ###   ########.fr       */
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

	cnt = 0;
	heredoc = exec_info->heredoc;
	while (cnt < exec_info->heredoc_cnt)
	{
		heredoc = heredoc->next;
		cnt++;
	}
	if (exec_info->fd[0] != -1)
	{
		close(exec_info->fd[0]);
		exec_info->fd[0] = -1;
	}
	close(heredoc->fd);
	heredoc->fd = open(heredoc->filename, O_RDONLY);
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
	get_line_with_fd("minidoc> ", here_end, fd);
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
