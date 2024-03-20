/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 14:53:43 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

//terminal
size_t	isio_file(t_ast *ast, t_token **token)
{
	if (ast->token_size < 2)
		return (0);
	if (token[0] \
	&& (token[0]->type == TDGREAT \
	|| token[0]->type == TDREAD \
	|| token[0]->type == TDWRITE) \
	&& token[1] && token[1]->type == TWORD)
	{
		ast->op = OPIO_FILE;
		ast->token_size = 2;
		add_ast(ast, token + 1, isfilename, 0, RIGHT);
		return (2);
	}
	return (0);
}

//terminal
size_t	isio_here(t_ast *ast, t_token **token)
{
	if (ast->token_size < 2)
		return (0);
	if (token[0] && token[0]->type == TDLESS \
	&& token[1] && token[1]->type == TWORD)
	{
		ast->op = OPIO_HERE;
		ast->token_size = 2;
		add_ast(ast, token + 1, ishere_end, 0, RIGHT);
		return (2);
	}
	return (0);
}

//terminal
size_t	isword(t_ast *ast, t_token **token)
{
	if (ast->token_size < 1)
		return (0);
	if (token[0] && token[0]->type == TWORD)
	{
		ast->op = OPWORD;
		ast->token_size = 1;
		return (1);
	}
	return (0);
}

//terminal
size_t	issubshell(t_ast *ast, t_token **token)
{
	size_t	cursor;

	if (ast->token_size < 3)
		return (0);
	cursor = 0;
	if (token[cursor] && token[cursor]->type == TLPAREN)
	{
		while (token[cursor] && token[cursor]->type != TRPAREN)
			cursor++;
		if (token[cursor] && token[cursor]->type == TRPAREN)
		{
			ast->op = OPSUBSHELL;
			ast->token_size = cursor + 1;
			return (cursor + 1);
		}
	}
	return (0);
}
