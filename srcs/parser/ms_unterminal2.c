/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unterminal2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 16:15:21 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

//unterminal
size_t	ms_is_simple_command(t_ast *ast, t_token **token)
{
	size_t	i;
	size_t	cursor;

	if (ast->token_size < 1)
		return (0);
	cursor = 0;
	if (token[cursor] && token[cursor]->type == TWORD)
	{
		cursor += ms_add_ast(ast, token + cursor, ms_is_cmd_word, 0, LEFT);
		if (cursor)
			cursor += ms_add_ast(ast, token + cursor, ms_is_cmd_suffix, 0, RIGHT);
	}
	else
	{
		cursor += ms_add_ast(ast, token + cursor, ms_is_cmd_prefix, 0, LEFT);
		if (cursor && token[cursor] && token[cursor]->type == TWORD)
		{
			cursor += ms_add_ast(ast, token + cursor, ms_is_cmd_word, 0, RIGHT);
			cursor += ms_add_ast(ast, token + cursor, ms_is_cmd_suffix, 0, RIGHT);
		}
	}
	ast->token_size = cursor;
	return (cursor);
}

//unterminal
size_t	ms_is_cmd_suffix(t_ast *ast, t_token **token)
{
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	cursor = 0;
	if (token[cursor] && (token[cursor]->type == TWORD))
		cursor += ms_add_ast(ast, token, ms_is_word, 0, RIGHT);
	else
		cursor += ms_add_ast(ast, token, ms_is_io_redirect, 0, LEFT);
	if (cursor)
		cursor += ms_add_ast(ast, token + cursor, ms_is_cmd_suffix, \
		ast->token_size - cursor, LEFT);
	ast->token_size = cursor;
	return (cursor);
}

//unterminal
size_t	ms_is_cmd_prefix(t_ast *ast, t_token **token)
{
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	cursor = 0;
	cursor += ms_add_ast(ast, token, ms_is_io_redirect, 0, LEFT);
	if (cursor)
		cursor += ms_add_ast(ast, token + cursor, ms_is_cmd_prefix, \
		ast->token_size - cursor, LEFT);
	ast->token_size = cursor;
	return (cursor);
}

//unterminal
size_t	ms_is_io_redirect(t_ast *ast, t_token **token)
{
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	cursor = 0;
	if (token[cursor] && (token[cursor]->type == TDLESS))
		cursor += ms_add_ast(ast, token + cursor, ms_is_io_here, 0, LEFT);
	else
		cursor += ms_add_ast(ast, token + cursor, ms_is_io_file, 0, LEFT);
	ast->token_size = cursor;
	return (cursor);
}
