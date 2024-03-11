/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:50:39 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/11 19:15:44 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	clear_syntax(t_syntax *syntax)
{
	int	i;

	i = 0;
	if (syntax->line)
		free(syntax->line);
	if (syntax->words)
	{
		while (syntax->words[i])
		{
			free(syntax->words[i++]);
			syntax->words[i] = NULL;
		}
		free(syntax->words);
		syntax->words = NULL;
	}
	syntax->words_cnt = 0;
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
	if (ast)
	{
		clear_ast(ast->left);
		clear_ast(ast->right);
		while (ast->token_size--)
		{
			if (ast->token[ast->token_size]->value)
			{
				free(ast->token[ast->token_size]->value);
				ast->token[ast->token_size]->value = NULL;
			}
			free(ast->token[ast->token_size]);
			ast->token[ast->token_size] = NULL;
		}
		free(ast);
		ast = NULL;
	}
}

void	clear_all(t_syntax *syntax, t_token **token, t_ast *ast)
{
	clear_syntax(syntax);
	clear_token(token);
	clear_ast(ast);
}

void	backtracking_free(t_ast **ast)
{
	if (*ast)
	{
		if (!((*ast)->token_size))
		{
			if ((*ast)->left)
			{
				free((*ast)->left);
				(*ast)->left = NULL;
			}
			if ((*ast)->right)
			{
				free((*ast)->right);
				(*ast)->right = NULL;
			}
			free((*ast));
			(*ast) = NULL;
		}
	}
}
