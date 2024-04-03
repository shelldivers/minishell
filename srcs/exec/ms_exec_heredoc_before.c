/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_heredoc_before.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:51:45 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/03 20:59:36 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "ms_exec.h"
#include "ms_parser.h"
#include <readline/readline.h>

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

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
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
		else if (!ft_strncmp(line, here_end, ft_strlen(here_end)))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	return (heredoc);
}

t_heredoc	*ms_remove_head(t_heredoc *heredoc)
{
	t_heredoc	*next;

	if (!heredoc)
		return (NULL);
	next = heredoc->next;
	free(heredoc->filename);
	free(heredoc);
	return (next);
}

t_bool	ms_set_heredoc(t_heredoc *heredoc, t_ast *ast, int heredoc_idx)
{
	char		*name;
	char		*filename;
	t_heredoc	*new_heredoc;

	name = ft_itoa(heredoc_idx);
	if (!name)
		return (FALSE);
	filename = ft_strjoin(".heredoc", name);
	if (!filename)
	{
		free(name);
		return (FALSE);
	}
	new_heredoc = ms_new_heredoc(filename, ast->token[1]->value);
	if (!new_heredoc)
		return (FALSE);
	ms_add_back_heredoc(&heredoc, new_heredoc);
	free(name);
	free(filename);
}

t_bool	ms_exec_heredoc_before(t_heredoc *heredoc, t_ast *ast, int idx)
{
	static int	heredoc_idx;

	if (!idx)
		heredoc_idx = 0;
	if (!ms_exec_heredoc_before(heredoc, ast->left, heredoc_idx))
		return (FALSE);
	if (ast->op == OPIO_HERE)
	{
		if (!ms_set_heredoc(heredoc, ast, heredoc_idx))
			return (FALSE);
		heredoc_idx++;
	}
	if (!ms_exec_heredoc_before(heredoc, ast->right, heredoc_idx))
		return (FALSE);
}
