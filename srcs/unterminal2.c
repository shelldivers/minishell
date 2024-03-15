/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unterminal2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/15 20:05:34 by jiwojung         ###   ########.fr       */
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

	i = 0;
	cursor = 0;
	while (token[i])
	{
		if (token[i]->type == TWORD)
		{
			cursor += addparse(ast, token + i, ast->token_size - i, isword, RIGHT);
			return (cursor);
		}
		i++;
	}
	return (cursor);
}

//unterminal
size_t	iscmd_suffix(t_ast *ast, t_token **token)
{
	size_t	cursor;

	cursor = 0;
	return (cursor);
}

//unterminal
size_t	iscmd_prefix(t_ast *ast, t_token **token)
{
	size_t	cursor;

	cursor = 0;
	return (cursor);
}

//unterminal
size_t	isio_redirect(t_ast *ast, t_token **token)
{
	size_t	cursor;

	cursor = 0;
	return (cursor);
}

