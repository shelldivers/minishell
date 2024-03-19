/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/19 19:52:57 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

//terminal
size_t	isio_file(t_ast *ast, t_token **token)
{
	ast->grammar = GIO_FILE;
	if (ast->token_size < 2)
		return (0);
	if (token[0] \
	&& (token[0]->type == TDGREAT \
	|| token[0]->type == TDREAD \
	|| token[0]->type == TDWRITE) \
	&& token[1] && token[1]->type == TWORD)
	{
		ast->token_size = 2;
		add_ast(ast, token + 1, isfilename, 0, LEFT);
		return (2);
	}
	return (0);
}

//terminal
size_t	isio_here(t_ast *ast, t_token **token)
{
	ast->grammar = GIO_HERE;
	if (ast->token_size < 2)
		return (0);
	if (token[0] && token[0]->type == TDLESS \
	&& token[1] && token[1]->type == TWORD)
	{
		ast->token_size = 2;
		add_ast(ast, token + 1, ishere_end, 0, LEFT);
		return (2);
	}
	return (0);
}

//terminal
size_t	isword(t_ast *ast, t_token **token)
{
	ast->grammar = GWORD;
	if (ast->token_size < 1)
		return (0);
	if (token[0] && token[0]->type == TWORD)
	{
		ast->token_size = 1;
		return (1);
	}
	return (0);
}

//terminal
size_t	isio_number(t_ast *ast, t_token **token)
{
	ast->grammar = GIO_NUMBER;
	if (ast->token_size < 1)
		return (0);
	if (token[0] && token[0]->type == GIO_NUMBER)
	{
		ast->token_size = 1;
		return (1);
	}
	return (0);
}

//terminal
size_t	issubshell(t_ast *ast, t_token **token)
{
	ast->grammar = GSUBSHELL;
	size_t	cursor;

	if (ast->token_size < 3)
		return (0);
	cursor = 0;
	if (token[cursor] && token[cursor]->type == TLPAREN)
	{
		while (token[cursor] && token[cursor]->type != TRPAREN)
			cursor++;
		if (token[cursor] && token[cursor]->type == TRPAREN)
		{
			ast->op = OPSUBSHELL;
			ast->token_size = cursor + 1;
			return (cursor + 1);
		}
	}
	return (0);
}
