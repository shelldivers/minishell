/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unterminal2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/17 19:55:53 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

//unterminal
size_t	issimple_command(t_ast *ast, t_token **token)
{
	size_t	i;
	size_t	cursor;

	i = 0;
	cursor = 0;
	if (token[i]->type == TWORD)
	{
		cursor += add_ast(ast, token + i, 1, iscmd_word, LEFT);
		cursor += add_ast(ast, token + i + 1, \
		ast->token_size - i - 1, iscmd_suffix, RIGHT);
	}
	else
	{
		cursor += add_ast(ast, token + i, 1, iscmd_prefix, LEFT);
		cursor += add_ast(ast, token + i + 1, \
		ast->token_size - i - 1, iscmd_name, RIGHT);
		cursor += add_ast(ast, token + i + 1, \
		ast->token_size - i - 1, iscmd_suffix, RIGHT);
	}
	i++;
	return (cursor);
}

//unterminal
size_t	iscmd_suffix(t_ast *ast, t_token **token)
{
	size_t	cursor;

	cursor = 0;
	cursor += add_ast(ast, token, ast->token_size, isio_redirect, LEFT);
	if (cursor)
		cursor += add_ast(ast, token + cursor, 
	else
		cursor += isword(ast, token);
	return (cursor);
}

//unterminal
size_t	iscmd_prefix(t_ast *ast, t_token **token)
{
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	cursor = 0;
	cursor += add_ast(ast, token, ast->token_size, isio_redirect, LEFT);
	if (cursor)
		iscmd_prefix(ast, token + cursor);
	return (cursor);
}

//unterminal
size_t	isio_redirect(t_ast *ast, t_token **token)
{
	size_t	cursor;

	cursor = 0;
	if (ast->token_size == 0)
		return (0);
	if (token[cursor] && (token[cursor]->type == TIO_NUMBER))
		cursor += add_ast(ast, token + cursor, 1, isio_number, LEFT);
	if (token[cursor] && (token[cursor]->type == TDLESS))
		cursor += add_ast(ast, token + cursor, 1, isio_here, LEFT);
	else
		cursor += add_ast(ast, token + cursor, 1, isio_file, LEFT);
	return (cursor);
}

