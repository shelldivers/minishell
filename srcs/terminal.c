/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/17 18:22:02 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

//terminal
size_t	isio_file(t_ast *ast, t_token **token)
{
	size_t	cursor;

	cursor = 0;
	if (ast->token_size == 0)
		return (0);
	if (token[cursor] && (token[cursor]->type == TDGREAT \
	|| token[cursor]->type == TDREAD || token[cursor]->type == TDWRITE))
	{
		if (token[cursor]->type == TDGREAT)
			ast->op = OPDGREAT;
		else if (token[cursor]->type == TDLESS)
			ast->op = OPDLESS;
		else if (token[cursor]->type == TDGREAT)
			ast->op = OPDGREAT;
		cursor++;
		cursor += add_ast(ast, token + cursor, 1, isfilename, LEFT);
	}
	else
		return (0);
	return (cursor);
}

//terminal
size_t	isio_here(t_ast *ast, t_token **token)
{
	size_t	cursor;

	cursor = 0;
	if (ast->token_size == 0)
		return (0);
	if (token[cursor] && token[cursor]->type == TDLESS)
		cursor += add_ast(ast, token, 1, ishere_end, LEFT);
	else
		return (0);
	return (cursor);
}

//terminal
size_t	isword(t_ast *ast, t_token **token)
{
	if (ast->token_size != 1)
		return (0);
	if (token[0] && token[0]->type == TWORD)
		return (1);
	return (0);
}

//terminal
size_t	isio_number(t_ast *ast, t_token **token)
{
	if (ast->token_size != 1)
		return (0);
	if (token[0] && token[0]->type == GIO_NUMBER)
		return (1);
	return (0);
}

//terminal
size_t	issubshell(t_ast *ast, t_token **token)
{
	size_t	cursor;
	size_t	count;

	if (ast->token_size == 0)
		return (0);
	cursor = 0;
	if (token[cursor] && token[cursor]->type == TLPAREN)
	{
		while (token[cursor] && token[cursor]->type != TRPAREN)
		{
			if (token[cursor] && \
			(token[cursor]->type == TAND_IF || token[cursor]->type == TOR_IF))
				count++;
			cursor++;
		}
		if (token[cursor] && token[cursor]->type == TRPAREN && count == 1)
		{
			ast->op = OPSUBSHELL;
			return (cursor);
		}
	}
	return (0);
}
