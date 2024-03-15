/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/15 20:16:47 by jiwojung         ###   ########.fr       */
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
		return (1);
	return (0);
}
//terminal
size_t	isio_number(t_ast *ast, t_token **token)
{
	if (ast->token_size == 0)
		return (0);
	if (token[0] && token[0]->type == GIO_NUMBER)
		return (1);
	return (0);
}

//terminal
size_t	issubshell(t_ast *ast, t_token **token)
{
	size_t	i;
	size_t	cursor;

	if (ast->token_size == 0)
		return (0);
	i = 0;
	cursor = 0;
	if (token[0] && token[0]->type == TLPAREN)
	{
		while (token[i] && token[i]->type != TRPAREN)
			i++;
		if (token[i] && token[i]->type == TRPAREN)
		{
			ast->op = OPSUBSHELL;
		}
	}
	return (0);
}
