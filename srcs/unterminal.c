/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unterminal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/19 19:54:35 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

static size_t	get_op_pos(t_token **token, enum e_type op);

//unterminal
size_t	isand_or(t_ast *ast, t_token **token)
{
	ast->grammar = GAND_OR;
	size_t	op_pos;
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	op_pos = get_op_pos(token, TAND_IF);
	if (!op_pos)
		op_pos = get_op_pos(token, TOR_IF);
	cursor = 0;
	if (op_pos && token[op_pos]->type == TAND_IF || token[op_pos]->type == TOR_IF)
	{
		cursor++;
		if (token[op_pos]->type == TAND_IF)
			ast->op = OPAND_IF;
		else
			ast->op = OPOR_IF;
		cursor += add_ast(ast, token, isand_or, op_pos, LEFT);
		cursor += add_ast(ast, token + op_pos + 1, ispipeline, \
		ast->token_size - op_pos - 1, RIGHT);
	}
	else
		cursor += add_ast(ast, token, ispipeline, 0, LEFT);
	return (cursor);
}

//unterminal
size_t	ispipeline(t_ast *ast, t_token **token)
{
	ast->grammar = GPIPELINE;
	size_t	op_pos;
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	op_pos = get_op_pos(token, TPIPE);
	cursor = 0;
	if (op_pos)
	{
		cursor++;
		ast->op = OPPIPE;
		cursor += add_ast(ast, token, ispipeline, op_pos, LEFT);
		cursor += add_ast(ast, token + op_pos + 1, iscommand, \
		ast->token_size - op_pos - 1, RIGHT);
	}
	else
		cursor += add_ast(ast, token, iscommand, 0, LEFT);
	return (cursor);
}

size_t	iscommand(t_ast *ast, t_token **token)
{
	ast->grammar = GCOMMAND;
	size_t	cursor;

	if (ast->token_size < 1)
		return (0);
	cursor = 0;
	if (token[cursor] && token[cursor] && token[cursor]->type == TLPAREN)
	{
		cursor += add_ast(ast, token + cursor, issubshell, 0, LEFT);
		if (cursor)
			cursor += add_ast(ast, token + cursor, isio_redirect, 0, RIGHT);
	}
	else
		cursor += add_ast(ast, token + cursor, issimple_command, 0, LEFT);
	ast->token_size = cursor;
	return (cursor);
}

static size_t	get_op_pos(t_token **token, enum e_type op)
{
	size_t	pos;

	pos = tokenlen(token);
	while (pos)
	{
		pos--;
		if (token[pos]->type == op)
			return (pos);
	}
	return (0);
}
