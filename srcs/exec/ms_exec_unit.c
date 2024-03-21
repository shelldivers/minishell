/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_unit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:10:51 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/21 17:47:26 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"

t_bool	ms_exec_if(t_ast *ast, t_exec *exec_info)
{
	return (TRUE);
}

t_bool	ms_exec_pipe(t_ast *ast, t_exec *exec_info)
{
	return (TRUE);
}

t_bool	ms_exec_subshell(t_ast *ast, t_exec *exec_info)
{
	return (TRUE);
}

t_bool	ms_exec_io_file(t_ast *ast, t_exec *exec_info)
{
	return (TRUE);
}

t_bool	ms_exec_io_here(t_ast *ast, t_exec *exec_info)
{
	char	*line;

	line = NULL;
	exec_info->fd[0] = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (exec_info->fd[0] == -1)
		return (FALSE);
	while (1)
	{
		line = get_next_line(0);
	}
	return (TRUE);
}

t_bool	ms_exec_cmd_word(t_ast *ast, t_exec *exec_info)
{
	exec_info->words = ms_create_words(ast->token[0]->value);
	if (!exec_info->words)
		return (FALSE);
	exec_info->words_size = 1;
	return (TRUE);
}

t_bool	ms_exec_word(char *word, t_exec *exec_info)
{
	exec_info->words = ms_add_word(\
	exec_info->words, word, exec_info->words_size);
	if (!exec_info->words)
		return (FALSE);
	exec_info->words_size++;
	return (TRUE);
}
