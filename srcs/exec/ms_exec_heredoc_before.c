/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_heredoc_before.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:51:45 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/04 10:49:50 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "ms_exec.h"
#include "ms_parser.h"
#include "libft.h"
#include <readline/readline.h>

static char	*ms_get_heredoc_filename(t_heredoc *heredoc, int idx);

t_bool	ms_exec_heredoc_before(t_heredoc **heredoc, t_ast *ast, int idx)
{
	static int	heredoc_idx;

	if (!ast)
		return (TRUE);
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
	return (TRUE);
}

t_bool	ms_set_heredoc(t_heredoc **heredoc, t_ast *ast, int heredoc_idx)
{
	char		*filename;
	t_heredoc	*new_heredoc;

	filename = ms_get_heredoc_filename(*heredoc, heredoc_idx);
	new_heredoc = ms_new_heredoc(filename, ast->token[1]->value);
	if (!new_heredoc)
		return (FALSE);
	ms_add_back_heredoc(heredoc, new_heredoc);
	return (TRUE);
}

static char	*ms_get_heredoc_filename(t_heredoc *heredoc, int idx)
{
	const char	*prefix = ".heredoc";
	const char	suffix[8] = {'1', '2', '3', '4', '5', '6', '7', '\0'};
	char		*filename;

	filename = ft_strjoin(prefix, &suffix[idx]);
	if (!filename)
		return (NULL);
	return (filename);
}
