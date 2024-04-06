/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unterminal2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/06 16:46:51 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_error.h"
#include "ms_parser.h"

static int	get_subshell_size(t_token **token);

int	ms_is_simple_command(t_ast *ast, t_token **token)
{
	const int	size = ms_get_token_size(token);
	int			curtok;
	int			tot_curtok;

	if (size < 1)
		return (0);
	tot_curtok = 0;
	if (token[0] && (token[0]->type == TWORD))
		curtok = ms_add_ast(ast, token, 0, (t_drill){ms_is_word, RIGHT});
	else
		curtok = ms_add_ast(ast, token, 0, \
		(t_drill){ms_is_redirect_list, LEFT});
	if (!ms_set_tot_curtok(&tot_curtok, curtok, 1))
		return (tot_curtok);
	if (tot_curtok < size)
	{
		curtok = ms_is_simple_command(ast, token + tot_curtok);
		if (!ms_set_tot_curtok(&tot_curtok, curtok, size - tot_curtok))
			return (tot_curtok);
	}
	return (tot_curtok);
}

int	ms_is_redirect_list(t_ast *ast, t_token **token)
{
	const int	size = ms_get_token_size(token);
	int			curtok;
	int			total_curtok;

	if (size < 0)
		return (0);
	total_curtok = 0;
	curtok = ms_add_ast(ast, token, size, (t_drill){ms_is_io_redirect, LEFT});
	if (!ms_set_tot_curtok(&total_curtok, curtok, 2))
			return (total_curtok);
	while (curtok)
	{
		curtok = ms_add_ast(ast, token + total_curtok, \
		0, (t_drill){ms_is_io_redirect, LEFT});
		if (!ms_set_tot_curtok(&total_curtok, curtok, 2))
			return (total_curtok);
	}
	return (total_curtok);
}

int	ms_is_io_redirect(t_ast *ast, t_token **token)
{
	const int	size = ms_get_token_size(token);
	int			curtok;

	if (size < 0)
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
	const int	size = ms_get_token_size(token);
	int			curtok;
	int			tot_curtok;
	int			subshell_size;

	if (size < 3)
		return (0);
	tot_curtok = 0;
	subshell_size = get_subshell_size(token);
	if (subshell_size)
	{
		curtok = ms_add_ast(ast, token + 1, \
		subshell_size - 2, (t_drill){ms_is_and_or, LEFT});
		if (!ms_set_tot_curtok(&tot_curtok, curtok, subshell_size - 2))
			return (tot_curtok + 1);
	}
	return (tot_curtok + 2);
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
