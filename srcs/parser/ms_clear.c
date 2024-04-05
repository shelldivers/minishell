/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:50:39 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/21 11:37:17 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_minishell.h"
#include "ms_parser.h"
#include <stdlib.h>

void	ms_clear_syntax(t_syntax *syntax)
{
	if (syntax)
	{
		if (syntax->line)
			free (syntax->line);
		if (syntax->words)
			ms_clear_sec_dimentional(syntax->words);
		ft_memset(syntax, 0, sizeof(t_syntax));
	}
}

void	ms_clear_token(t_token **token)
{
	int	i;

	if (token)
	{
		i = 0;
		while (token[i])
		{
			free(token[i]->value);
			free(token[i]);
			i++;
		}
		free(token);
	}
}

void	ms_clear_ast(t_ast *ast)
{
	t_ast	*left;
	t_ast	*right;

	if (ast)
	{
		left = ast->left;
		right = ast->right;
		ms_clear_token(ast->token);
		free(ast);
		ms_clear_ast(left);
		ms_clear_ast(right);
	}
}
