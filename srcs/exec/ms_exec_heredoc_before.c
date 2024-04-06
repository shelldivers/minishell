/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_heredoc_before.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:51:45 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 14:04:17 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_error.h"
#include "ms_exec.h"
#include "ms_signal.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_bool	ms_exec_heredoc_before(t_ast *ast)
{
	int			pid;
	int			status;

	pid = fork();
	if (pid < 0)
		ms_puterror_fork();
	if (pid == 0)
	{
		ms_set_signal_heredoc();
		if (ms_here_doc_in_order(ast, 0) == FALSE)
			exit(1);
		exit(0);
	}
	else
	{
		ms_set_signal_ignore();
		waitpid(pid, &status, 0);
		ms_set_signal_prompt();
		if (wifexit(status) && wexitstatus(status) == 1)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	ms_here_doc_in_order(t_ast *ast, int num)
{
	static int	seq;

	if (!num)
		seq = 0;
	if (!ast)
		return (TRUE);
	if (ms_here_doc_in_order(ast->left, seq) == FALSE)
		return (FALSE);
	if (ast->op == OPIO_HERE)
	{
		if (ms_set_heredoc(ast, seq) == FALSE)
			return (FALSE);
		seq++;
	}
	if (ms_here_doc_in_order(ast->right, seq) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_bool	ms_set_heredoc(t_ast *ast, const int seq)
{
	int		fd;
	char	*filename;
	char	*here_end;

	filename = ms_get_heredoc_filename(seq);
	if (!filename)
	{
		ms_puterror_cmd(NULL, "malloc");
		return (FALSE);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ms_puterror_cmd(NULL, "open");
		return (FALSE);
	}
	here_end = ms_quote_removal_dup(ast->token[1]->value, 0, 0);
	ms_get_line_with_fd(HEREDOC, here_end, fd);
	if (close(fd) == -1)
		ms_puterror_cmd(NULL, "close");
	free (filename);
	free (here_end);
	return (TRUE);
}

char	*ms_get_heredoc_filename(int idx)
{
	char		*filename;

	filename = ft_sprintf("%s_%d", SHELLNAME, idx);
	if (!filename)
		return (NULL);
	return (filename);
}
