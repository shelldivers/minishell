/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isgrammar2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/11 19:21:36 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

//unterminal
size_t	issimple_command(t_ast *ast, t_token **token)
{
	return (0);
}

//unterminal
size_t	iscmd_suffix(t_ast *ast, t_token **token)
{
	return (0);
}

//unterminal
size_t	iscmd_prefix(t_ast *ast, t_token **token)
{
	size_t	cursor;

	/*==============================================*/
	ast->grammar = GCMD_PREFIX;
	printf("iscmd_prefix\n");
	for (size_t j = 0; j < ast->token_size; j++)
		printf("%s ", token[j]->value);
	/*==============================================*/

	cursor = 0;
	while (ast->token_size - cursor)
	{
		cursor++;
		if 
	}
	return (0);
}

//unterminal
size_t	isio_redirect(t_ast *ast, t_token **token)
{
	size_t	cursor;

	/*==============================================*/
	ast->grammar = GIO_REDIRECT;
	printf("isio_redirect\n");
	for (size_t j = 0; j < ast->token_size; j++)
		printf("%s ", token[j]->value);
	/*==============================================*/

	if (ast->token_size < 2)
		return (0);
	cursor = 0;
	if (token[0] && (token[0]->type == TDREAD \
	|| token[0]->type == TDWRITE || token[0]->type == TDGREAT) \
	&& token[1] && token[1]->type == TWORD)
	{
		cursor += add_ast(ast, token + 2, ast->token_size - 2, isio_file, LEFT);
		return (2);
	}
	else if (token[0] && token[0]->type == TDLESS \
	&& token[1] && token[1]->type == TWORD)
	{
		cursor += add_ast(ast, token + 2, ast->token_size - 2, isio_here, LEFT);
		return (2);
	}
	return (0);
}
