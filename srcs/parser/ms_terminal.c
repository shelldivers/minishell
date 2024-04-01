/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/01 19:57:26 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

size_t	ms_is_io_file(t_ast *ast, t_token **token)
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
		return (2);
	}
	return (0);
}

size_t	ms_is_io_here(t_ast *ast, t_token **token)
{
	if (ast->token_size < 2)
		return (0);
	if (token[0] && token[0]->type == TDLESS \
	&& token[1] && token[1]->type == TWORD)
	{
		ast->op = OPIO_HERE;
		ast->token_size = 2;
		return (2);
	}
	return (0);
}

size_t	ms_is_word(t_ast *ast, t_token **token)
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

size_t	ms_is_subshell(t_ast *ast, t_token **token)
{
	size_t	curtok;
	size_t	lparen;
	size_t	rparen;

	if (ast->token_size < 3)
		return (0);
	curtok = 0;
	lparen = 0;
	rparen = 0;
	while (token[curtok])
	{
		if (token[curtok]->type == TLPAREN)
			lparen++;
		else if (token[curtok]->type == TRPAREN)
			rparen++;
		if (token[curtok] && lparen == rparen)
		{
			ast->op = OPSUBSHELL;
			ast->token_size = curtok + 1;
			return (curtok + 1);
		}
		curtok++;
	}
	return (0);
}
