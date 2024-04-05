/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unterminal2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 20:08:13 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

static int	get_subshell_size(t_token **token);

int	ms_is_simple_command(t_ast *ast, t_token **token)
{
	int	beftok;
	int	curtok;

	if (ast->token_size < 1)
		return (0);
	curtok = 0;
	beftok = 0;
	if (token[curtok] && (token[curtok]->type == TWORD))
		curtok += ms_add_ast(ast, token, \
		0, (t_drill){ms_is_word, LEFT});
	else
		curtok += ms_add_ast(ast, token, \
		0, (t_drill){ms_is_io_redirect, LEFT});
	while (token[curtok] && curtok > beftok)
	{
		beftok = curtok;
		if (token[curtok]->type == TWORD)
			curtok += ms_add_ast(ast, token + curtok, \
			0, (t_drill){ms_is_word, LEFT});
		else
			curtok += ms_add_ast(ast, token + curtok, \
			0, (t_drill){ms_is_io_redirect, LEFT});
	}
	ast->token_size = curtok;
	return (curtok);
}

int	ms_is_redirect_list(t_ast *ast, t_token **token)
{
	int	curtok;
	int	total_curtok;

	if (ast->token_size == 0)
		return (0);
	curtok = 0;
	total_curtok = 0;
	curtok += ms_add_ast(ast, token + total_curtok, \
	ast->token_size - total_curtok, (t_drill){ms_is_io_redirect, LEFT});
	while (curtok)
	{
		total_curtok += curtok;
		curtok = 0;
		curtok += ms_add_ast(ast, token + total_curtok, \
		ast->token_size - total_curtok, (t_drill){ms_is_io_redirect, LEFT});
	}
	return (total_curtok);
}

int	ms_is_io_redirect(t_ast *ast, t_token **token)
{
	int	curtok;

	if (ast->token_size == 0)
		return (0);
	curtok = 0;
	if (token[curtok] && (token[curtok]->type == TDLESS))
		curtok += ms_is_io_here(ast, token);
	else
		curtok += ms_is_io_file(ast, token);
	return (curtok);
}

int	ms_is_subshell(t_ast *ast, t_token **token)
{
	int	curtok;
	int	subshell_size;

	curtok = 0;
	subshell_size = get_subshell_size(token);
	if (subshell_size)
	{
		curtok += ms_add_ast(ast, token + 1, \
		subshell_size - 2, (t_drill){ms_is_and_or, LEFT});
		return (curtok + 2);
	}
	return (0);
}

static int	get_subshell_size(t_token **token)
{
	int	curtok;
	int	paren;

	curtok = 0;
	paren = 0;
	while (token[curtok])
	{
		if (token[curtok]->type == TLPAREN)
			paren++;
		else if (token[curtok]->type == TRPAREN && paren > 0)
			paren--;
		else if ((token[curtok]->type == TRPAREN && paren == 0))
			return (0);
		if (token[curtok] && token[curtok]->type == TRPAREN && paren == 0)
			return (curtok + 1);
		curtok++;
	}
	return (0);
}
