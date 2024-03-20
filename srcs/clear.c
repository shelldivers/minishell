/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:50:39 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 14:28:56 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "../libft/includes/libft.h"

void	clear_syntax(t_syntax *syntax)
{
	int	i;

	i = 0;
	if (syntax)
	{
		if (syntax->line)
			free (syntax->line);
		syntax->line = NULL;
		if (syntax->words)
		{
			while (syntax->words[i])
			{
				free(syntax->words[i]);
				syntax->words[i] = NULL;
				i++;
			}
			free (syntax->words);
			syntax->words = NULL;
		}
	}
}

void	clear_token(t_token **token)
{
	int	i;

	i = 0;
	if (token)
	{
		while (token[i])
		{
			free(token[i]->value);
			token[i]->value = NULL;
			free(token[i]);
			token[i] = NULL;
			i++;
		}
		free(token);
		token = NULL;
	}
}

void	clear_ast(t_ast *ast)
{
	t_ast	*left;
	t_ast	*right;

	if (ast)
	{
		left = ast->left;
		right = ast->right;
		if (ast->token)
		{
			clear_token(ast->token);
			ast->token = NULL;
		}
		free(ast);
		ast = NULL;
		clear_ast(left);
		clear_ast(right);
	}
}
