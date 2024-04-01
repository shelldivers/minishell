/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unterminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/01 19:58:36 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ms_parser.h"

size_t	ms_is_and_or(t_ast *ast, t_token **token)
{
	size_t	op_pos;
	size_t	curtok;

	if (ast->token_size == 0)
		return (0);
	op_pos = ms_get_op_pos(token, TAND_IF, TOR_IF);
	curtok = 0;
	if (op_pos && (token[op_pos]->type == TAND_IF \
	|| token[op_pos]->type == TOR_IF))
	{
		if (token[op_pos]->type == TAND_IF)
			ast->op = OPAND_IF;
		else
			ast->op = OPOR_IF;
		curtok += ms_add_ast(ast, token + op_pos + 1, ms_is_pipeline, \
		ast->token_size - op_pos - 1, RIGHT);
		if (curtok)
			curtok += ms_add_ast(ast, token, ms_is_and_or, op_pos, LEFT);
		curtok++;
	}
	else
		curtok += ms_add_ast(ast, token, ms_is_pipeline, 0, LEFT);
	if (curtok == ast->token_size)
		return (curtok);
	return (ast->token_size - curtok);
}

size_t	ms_is_pipeline(t_ast *ast, t_token **token)
{
	size_t	op_pos;
	size_t	curtok;

	if (ast->token_size == 0)
		return (0);
	op_pos = ms_get_op_pos(token, TPIPE, TNONE);
	curtok = 0;
	if (op_pos)
	{
		ast->op = OPPIPE;
		curtok += ms_add_ast(ast, token + op_pos + 1, ms_is_command, \
		ast->token_size - op_pos - 1, RIGHT);
		if (curtok)
			curtok += ms_add_ast(ast, token, ms_is_pipeline, op_pos, LEFT);
		curtok++;
	}
	else
		curtok += ms_add_ast(ast, token, ms_is_command, 0, LEFT);
	if (curtok == ast->token_size)
		return (curtok);
	return (ast->token_size - curtok);
}

size_t	ms_is_command(t_ast *ast, t_token **token)
{
	size_t	curtok;

	if (ast->token_size < 1)
		return (0);
	curtok = 0;
	if (token[curtok] && token[curtok]->type == TLPAREN)
	{
		curtok += ms_add_ast(ast, token + curtok, ms_is_subshell, 0, RIGHT);
		if (curtok)
			curtok += ms_add_ast(ast, token + curtok, ms_is_redirect_list, \
			0, LEFT);
	}
	else
		curtok += ms_add_ast(ast, token + curtok, ms_is_simple_command, \
		0, LEFT);
	ast->token_size = curtok;
	return (curtok);
}

size_t	ms_get_op_pos(t_token **token, enum e_type op1, enum e_type op2)
{
	size_t	pos1;
	size_t	pos2;

	if (token == NULL)
		return (0);
	pos1 = ms_tokenlen(token);
	pos2 = ms_tokenlen(token);
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
