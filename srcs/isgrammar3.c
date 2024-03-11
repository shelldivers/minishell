/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isgrammar3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/11 19:41:17 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

//terminal
size_t	isio_file(t_ast *ast, t_token **token)
{
	size_t	cursor;

	cursor = 0;
	cursor += addparse(ast, token, ast->token_size, isword, RIGHT);
	if (token[ast->token_size - cursor - 1]->type == TDREAD)
	{
		ast->op = OPDREAD;
		cursor++;
	}
	else if (token[0]->type == TDWRITE)
	{
		ast->op = OPDWRITE;
		
	}
	else if (token[0]->type == TDGREAT)
	{
		ast->op = OPDGREAT;
	}
}

//terminal
size_t	isio_here(t_ast *ast, t_token **token)
{
	size_t	cursor;

	cursor = 0;
	ast->op = OPDLESS;
	cursor += addparse(ast, token, ast->token_size, isio_number, LEFT);
	cursor += addparse(ast, token + cursor, ast->token_size, isword, RIGHT);
	return (0);
}

//terminal
size_t	isword(t_ast *ast, t_token **token)
{
	if (ast->token_size == 0)
		return (0);
	if (token[0] && token[0]->type == TWORD)
	{
		ast->token_size = 1;
		return (1);
	}
	return (0);
}

size_t	isio_number(t_ast *ast, t_token **token)
{
	if (ast->token_size == 0)
		return (0);
	if (token[0] && token[0]->type == GIO_NUMBER)
	{
		ast->token_size = 1;
		return (1);
	}
	return (0);
}
