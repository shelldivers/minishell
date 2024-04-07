/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unterminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/07 15:03:11 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"
#include "ms_error.h"
#include "ft_bool.h"
#include <stdio.h>

// TODO: 변경
int	ms_is_and_or(t_ast *ast, t_token **token)
{
	const int	size = ms_get_token_size(token);
	int			op_pos;
	int			curtok;
	int			tot_curtok;

	if (size < 1)
		return (0);
	tot_curtok = 0;
	op_pos = ms_get_op_pos(token, TAND_IF, TOR_IF);
	if (!op_pos)
		return (ms_add_ast(ast, token, 0, (t_drill){ms_is_pipeline, LEFT}));
	ast->op = OPOR_IF;
	if (token[op_pos]->type == TAND_IF)
		ast->op = OPAND_IF;
	curtok = ms_add_ast(ast, token, op_pos, (t_drill){ms_is_and_or, LEFT});
	if (!ms_set_tot_curtok(&tot_curtok, curtok, op_pos))
		return (tot_curtok);
	curtok = ms_add_ast(ast, token + op_pos + 1, (int)size - op_pos - 1, \
	(t_drill){ms_is_pipeline, RIGHT});
	if (!ms_set_tot_curtok(&tot_curtok, curtok, (int)size - op_pos - 1))
		return (tot_curtok);
	return (tot_curtok + 1);
}

int	ms_is_pipeline(t_ast *ast, t_token **token)
{
	const int	size = ms_get_token_size(token);
	int			op_pos;
	int			curtok;
	int			tot_curtok;

	if (size < 1)
		return (0);
	tot_curtok = 0;
	op_pos = ms_get_op_pos(token, TPIPE, TNONE);
	if (!op_pos)
		return (ms_add_ast(ast, token, 0, (t_drill){ms_is_command, LEFT}));
	ast->op = OPPIPE;
	curtok = ms_add_ast(ast, token, op_pos, (t_drill){ms_is_pipeline, LEFT});
	if (!ms_set_tot_curtok(&tot_curtok, curtok, op_pos))
		return (tot_curtok);
	curtok = ms_add_ast(ast, token + op_pos + 1, (int)size - op_pos - 1, \
	(t_drill){ms_is_pipeline, RIGHT});
	if (!ms_set_tot_curtok(&tot_curtok, curtok, (int)size - op_pos - 1))
		return (tot_curtok);
	return (tot_curtok + 1);
}

int	ms_is_command(t_ast *ast, t_token **token)
{
	const int	size = ms_get_token_size(token);
	int			curtok;
	int			tot_curtok;

	if (size < 1)
		return (0);
	tot_curtok = 0;
	if (token[0]->type != TLPAREN)
		return (ms_add_ast(ast, token, 0, \
		(t_drill){ms_is_simple_command, LEFT}));
	curtok = ms_add_ast(ast, token, 0, (t_drill){ms_is_subshell, LEFT});
	if (!ms_set_tot_curtok(&tot_curtok, curtok, 3))
		return (tot_curtok);
	while (tot_curtok < size)
	{
		curtok = ms_add_ast(ast, token + tot_curtok, size - tot_curtok, \
		(t_drill){ms_is_io_redirect, LEFT});
		if (!ms_set_tot_curtok(&tot_curtok, curtok, 2))
			return (tot_curtok);
	}
	return (tot_curtok);
}

int	ms_get_op_pos(t_token **token, enum e_type op1, enum e_type op2)
{
	int	op_idx;
	int	curtok;
	int	paren;

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
		{
			op_idx = curtok;
		}
		curtok++;
	}
	return (op_idx);
}

t_bool	ms_set_tot_curtok(int *tot_curtok, int curtok, int expected_size)
{
	if (curtok == ERROR)
	{
		*tot_curtok = ERROR;
		return (FALSE);
	}
	else if (!curtok || curtok < expected_size)
	{
		*tot_curtok += curtok;
		return (FALSE);
	}
	*tot_curtok += curtok;
	return (TRUE);
}
