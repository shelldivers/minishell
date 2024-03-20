/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unterminal2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 14:52:23 by jiwojung         ###   ########.fr       */
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

	if (ast->token_size < 1)
		return (0);
	cursor = 0;
	if (token[cursor] && token[cursor]->type == TWORD)
	{
		cursor += add_ast(ast, token + cursor, iscmd_word, 0, LEFT);
		if (cursor)
			cursor += add_ast(ast, token + cursor, iscmd_suffix, 0, RIGHT);
	}
	else
	{
		cursor += add_ast(ast, token + cursor, iscmd_prefix, 0, LEFT);
		if (cursor && token[cursor] && token[cursor]->type == TWORD)
		{
			cursor += add_ast(ast, token + cursor, iscmd_word, 0, RIGHT);
			cursor += add_ast(ast, token + cursor, iscmd_suffix, 0, RIGHT);
		}
	}
	ast->token_size = cursor;
	return (cursor);
}

//unterminal
size_t	iscmd_suffix(t_ast *ast, t_token **token)
{
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	cursor = 0;
	if (token[cursor] && (token[cursor]->type == TWORD))
		cursor += add_ast(ast, token, isword, 0, RIGHT);
	else
		cursor += add_ast(ast, token, isio_redirect, 0, LEFT);
	if (cursor)
		cursor += add_ast(ast, token + cursor, iscmd_suffix, \
		ast->token_size - cursor, LEFT);
	ast->token_size = cursor;
	return (cursor);
}

//unterminal
size_t	iscmd_prefix(t_ast *ast, t_token **token)
{
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	cursor = 0;
	cursor += add_ast(ast, token, isio_redirect, 0, LEFT);
	if (cursor)
		cursor += add_ast(ast, token + cursor, iscmd_prefix, \
		ast->token_size - cursor, LEFT);
	ast->token_size = cursor;
	return (cursor);
}

//unterminal
size_t	isio_redirect(t_ast *ast, t_token **token)
{
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	cursor = 0;
	if (token[cursor] && (token[cursor]->type == TDLESS))
		cursor += add_ast(ast, token + cursor, isio_here, 0, LEFT);
	else
		cursor += add_ast(ast, token + cursor, isio_file, 0, LEFT);
	ast->token_size = cursor;
	return (cursor);
}
