/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unterminal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/17 13:25:52 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

//unterminal
size_t	isand_or(t_ast *ast, t_token **token)
{
	size_t	i;
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	cursor = 0;
	i = ast->token_size;
	while (i-- > 0)
	{
		if (token[i]->type == TAND_IF || token[i]->type == TOR_IF)
		{
			if (token[i]->type == TAND_IF)
				ast->op = OPAND_IF;
			else
				ast->op = OPOR_IF;
			cursor += add_ast(ast, token, i - 1, isand_or, LEFT);
			cursor += add_ast(ast, token + i + 1, \
			ast->token_size - i, ispipeline, RIGHT);
			return (cursor + 1);
		}
		cursor += add_ast(ast, token, ast->token_size, ispipeline, LEFT);
	}
	return (cursor);
}

//unterminal
size_t	ispipeline(t_ast *ast, t_token **token)
{
	size_t	i;
	size_t	cursor;

	cursor = 0;
	i = 0;
	while (i-- > 0)
	{
		if (token[i]->type == TPIPE)
		{
			ast->op = OPPIPE;
			cursor += add_ast(ast, token, i - 1, ispipeline, LEFT);
			cursor += add_ast(ast, token + i + 1, \
			ast->token_size - i, iscommand, RIGHT);
			return (cursor + 1);
		}
		cursor += add_ast(ast, token, ast->token_size, iscommand, LEFT);
	}
	return (cursor);
}

size_t	iscommand(t_ast *ast, t_token **token)
{
	size_t	cursor;

	cursor = 0;
	if (token[0]->type == TLPAREN)
	{
		cursor += add_ast(ast, token, ast->token_size, issubshell, LEFT);
		cursor += add_ast(ast, token + cursor, ast->token_size - cursor, \
		isio_redirect, RIGHT);
	}
	else
		cursor += add_ast(ast, token, ast->token_size, issimple_command, LEFT);
	return (cursor);
}


