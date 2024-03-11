/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isgrammar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/11 19:13:46 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

//unterminal
size_t	isand_or(t_ast *ast, t_token **token)
{
	size_t	i;
	size_t	cursor;

	/*==============================================*/
	if (ast->token_size == 0)
		return (0);
	printf("isand_or\n");
	for (size_t j = 0; j < ast->token_size; j++)
		printf("%s ", token[j]->value);
	printf("\n");
	ast->grammar = GAND_OR;
	/*==============================================*/
	i = ast->token_size - 1;
	cursor = 0;
	while (i)
	{
		if (token[i] && token[i]->type == TAND_IF)
		{
			cursor += add_ast(ast, token + i + 1, ast->token_size - i - 1, \
			ispipeline, RIGHT);
			cursor += add_ast(ast, token, i - 1, \
			ispipeline, LEFT);
			ast->op = OPAND_IF;
			return (1);
		}
		else if (token[i] && token[i]->type == TOR_IF)
		{
			cursor += add_ast(ast, token + i + 1, ast->token_size - i - 1, \
			ispipeline, RIGHT);
			cursor += add_ast(ast, token, i - 1, \
			ispipeline, LEFT);
			ast->op = OPOR_IF;
			return (1);
		}
		i--;
	}
	return (cursor);
}

//unterminal
size_t	ispipeline(t_ast *ast, t_token **token)
{
	size_t	i;
	size_t	cursor;

	/*==============================================*/
	if (ast->token_size == 0)
		return (0);
	printf("ispipeline\n");
	for (size_t j = 0; j < ast->token_size; j++)
		printf("%s ", token[j]->value);
	printf("\n");
	ast->grammar = GPIPELINE;
	/*==============================================*/
	i = ast->token_size - 1;
	cursor = 0;
	return (1);
}

size_t	iscommand(t_ast *ast, t_token **token)
{
	size_t	i;
	size_t	cursor;

	/*==============================================*/
	if (ast->token_size == 0)
		return (0);
	printf("iscommand\n");
	for (size_t j = 0; j < ast->token_size; j++)
		printf("%s ", token[j]->value);
	printf("\n");
	ast->grammar = GCOMMAND;
	/*==============================================*/
	i = ast->token_size - 1;
	cursor = 0;
	if (token[0] && token[0]->type == TLBRACE)
	{
		cursor += add_ast(ast, token + 1, ast->token_size - 2, \
		issubshell, LEFT);
		cursor += add_ast(ast, token + ast->token_size - 1, 1, \
		isio_redirect, RIGHT);
	}
	else
	{
		
	}
	return (cursor);
}

//terminal
size_t	issubshell(t_ast *ast, t_token **token)
{
	size_t	i;
	size_t	cursor;

	/*==============================================*/
	if (ast->token_size == 0)
		return (0);
	printf("issubshell\n");
	for (size_t j = 0; j < ast->token_size; j++)
		printf("%s ", token[j]->value);
	printf("\n");
	ast->grammar = GSUBSHELL;
	/*==============================================*/
	i = ast->token_size - 1;
	cursor = 0;
	return (1);
}
