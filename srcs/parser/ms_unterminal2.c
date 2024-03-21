/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unterminal2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/21 10:26:08 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ms_parser.h"

size_t	ms_is_simple_command(t_ast *ast, t_token **token)
{
	size_t	i;
	size_t	curtok;

	if (ast->token_size < 1)
		return (0);
	curtok = 0;
	if (token[curtok] && token[curtok]->type == TWORD)
	{
		curtok += ms_add_ast(ast, token + curtok, ms_is_cmd_word, 0, LEFT);
		if (curtok)
			curtok += ms_add_ast(ast, token + curtok, ms_is_cmd_suffix, \
			0, RIGHT);
	}
	else
	{
		curtok += ms_add_ast(ast, token + curtok, ms_is_cmd_prefix, 0, LEFT);
		if (curtok && token[curtok] && token[curtok]->type == TWORD)
		{
			curtok += ms_add_ast(ast, token + curtok, ms_is_cmd_word, 0, RIGHT);
			curtok += ms_add_ast(ast, token + curtok, ms_is_cmd_suffix, \
			0, RIGHT);
		}
	}
	ast->token_size = curtok;
	return (curtok);
}

size_t	ms_is_cmd_suffix(t_ast *ast, t_token **token)
{
	size_t	curtok;

	if (ast->token_size == 0)
		return (0);
	curtok = 0;
	if (token[curtok] && (token[curtok]->type == TWORD))
		curtok += ms_add_ast(ast, token, ms_is_word, 0, RIGHT);
	else
		curtok += ms_add_ast(ast, token, ms_is_io_redirect, 0, LEFT);
	if (curtok)
		curtok += ms_add_ast(ast, token + curtok, ms_is_cmd_suffix, \
		ast->token_size - curtok, LEFT);
	ast->token_size = curtok;
	return (curtok);
}

size_t	ms_is_cmd_prefix(t_ast *ast, t_token **token)
{
	size_t	curtok;

	if (ast->token_size == 0)
		return (0);
	curtok = 0;
	curtok += ms_add_ast(ast, token, ms_is_io_redirect, 0, LEFT);
	if (curtok)
		curtok += ms_add_ast(ast, token + curtok, ms_is_cmd_prefix, \
		ast->token_size - curtok, LEFT);
	ast->token_size = curtok;
	return (curtok);
}

size_t	ms_is_io_redirect(t_ast *ast, t_token **token)
{
	size_t	curtok;

	if (ast->token_size == 0)
		return (0);
	curtok = 0;
	if (token[curtok] && (token[curtok]->type == TDLESS))
		curtok += ms_add_ast(ast, token + curtok, ms_is_io_here, 0, LEFT);
	else
		curtok += ms_add_ast(ast, token + curtok, ms_is_io_file, 0, LEFT);
	ast->token_size = curtok;
	return (curtok);
}
