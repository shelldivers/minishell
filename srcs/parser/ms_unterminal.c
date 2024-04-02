/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unterminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/02 17:25:11 by jiwojung         ###   ########.fr       */
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
	return (curtok);
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
	return (curtok);
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
		{
			curtok += ms_add_ast(ast, token + curtok, ms_is_redirect_list, \
			0, LEFT);
		}
	}
	else
		curtok += ms_add_ast(ast, token + curtok, ms_is_simple_command, \
		0, LEFT);
	ast->token_size = curtok;
	return (curtok);
}

size_t	ms_get_op_pos(t_token **token, enum e_type op1, enum e_type op2)
{
	size_t	op_idx;
	size_t	curtok;
	size_t	paren;

	if (token == NULL)
		return (0);
	op_idx = 0;
	curtok = 0;
	paren = 0;
	while (token[curtok])
	{
		if (token[curtok]->type == TLPAREN)
			paren++;
		else if (token[curtok]->type == TRPAREN && paren > 0)
			paren--;
		else if (token[curtok]->type == TRPAREN && paren == 0)
			return (0);
		if ((token[curtok]->type == op1 \
		|| token[curtok]->type == op2) && paren == 0)
			op_idx = curtok;
		curtok++;
	}
	return (op_idx);
}
