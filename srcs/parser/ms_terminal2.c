/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_terminal2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:09:38 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 16:07:12 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

//terminal
size_t	ms_is_filename(t_ast *ast, t_token **token)
{
	if (ast->token_size < 1)
		return (0);
	if (token[0] && token[0]->type == TWORD)
	{
		ast->token_size = 1;
		return (1);
	}
	return (0);
}

//terminal
size_t	ms_is_here_end(t_ast *ast, t_token **token)
{
	if (ast->token_size < 1)
		return (0);
	if (token[0] && token[0]->type == TWORD)
	{
		ast->token_size = 1;
		return (1);
	}
	return (0);
}

size_t	ms_is_cmd_name(t_ast *ast, t_token **token)
{
	if (ast->token_size < 1)
		return (0);
	if (token[0] && token[0]->type == TWORD)
	{
		ast->op = OPCMD_NAME;
		ast->token_size = 1;
		return (1);
	}
	return (0);
}

size_t	ms_is_cmd_word(t_ast *ast, t_token **token)
{
	if (ast->token_size < 1)
		return (0);
	if (token[0] && token[0]->type == TWORD)
	{
		ast->op = OPCMD_WORD;
		ast->token_size = 1;
		return (1);
	}
	return (0);
}
