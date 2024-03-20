/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_terminal2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:09:38 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 17:54:38 by jiwojung         ###   ########.fr       */
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
