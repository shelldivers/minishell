/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unterminal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 14:55:10 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

static size_t	get_op_pos(t_token **token, enum e_type op1, enum e_type op2);

//unterminal
size_t	isand_or(t_ast *ast, t_token **token)
{
	size_t	op_pos;
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	op_pos = get_op_pos(token, TAND_IF, TOR_IF);
	cursor = 0;
	if (op_pos && token[op_pos]->type == TAND_IF \
	|| token[op_pos]->type == TOR_IF)
	{
		if (token[op_pos]->type == TAND_IF)
			ast->op = OPAND_IF;
		else
			ast->op = OPOR_IF;
		cursor += add_ast(ast, token + op_pos + 1, ispipeline, \
		ast->token_size - op_pos - 1, RIGHT);
		if (cursor)
			cursor += add_ast(ast, token, isand_or, op_pos, LEFT);
		cursor++;
	}
	else
		cursor += add_ast(ast, token, ispipeline, 0, LEFT);
	if (cursor == ast->token_size)
		return (cursor);
	return (ast->token_size - cursor);
}

//unterminal
size_t	ispipeline(t_ast *ast, t_token **token)
{
	size_t	op_pos;
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	op_pos = get_op_pos(token, TPIPE, TNONE);
	cursor = 0;
	if (op_pos)
	{
		ast->op = OPPIPE;
		cursor += add_ast(ast, token + op_pos + 1, iscommand, \
		ast->token_size - op_pos - 1, RIGHT);
		if (cursor)
			cursor += add_ast(ast, token, ispipeline, op_pos, LEFT);
		cursor++;
	}
	else
		cursor += add_ast(ast, token, iscommand, 0, LEFT);
	if (cursor == ast->token_size)
		return (cursor);
	return (ast->token_size - cursor);
}

size_t	iscommand(t_ast *ast, t_token **token)
{
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

static size_t	get_op_pos(t_token **token, enum e_type op1, enum e_type op2)
{
	size_t	pos1;
	size_t	pos2;

	if (token == NULL)
		return (0);
	pos1 = tokenlen(token);
	pos2 = tokenlen(token);
	while (pos1)
	{
		pos1--;
		if (token[pos1]->type == op1)
			break ;
	}
	if (op2 != TNONE)
	{
		while (pos2)
		{
			pos2--;
			if (token[pos2]->type == op2)
				break ;
		}
		if (pos1 < pos2)
			return (pos2);
	}
	return (pos1);
}
