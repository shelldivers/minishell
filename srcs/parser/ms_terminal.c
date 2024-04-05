/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/02 14:24:18 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

int	ms_is_io_file(t_ast *ast, t_token **token)
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

int	ms_is_io_here(t_ast *ast, t_token **token)
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

int	ms_is_word(t_ast *ast, t_token **token)
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
