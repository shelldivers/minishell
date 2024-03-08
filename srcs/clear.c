/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:50:39 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/08 18:56:55 by jiwojung         ###   ########.fr       */
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

void	clear_parse(t_parse *parse)
{
	if (parse)
	{
		clear_parse(parse->left);
		clear_parse(parse->right);
		while (parse->token_size--)
		{
			if (parse->token[parse->token_size]->value)
				free(parse->token[parse->token_size]->value);
			free(parse->token[parse->token_size]);
		}
		free(parse);
	}
}

void	clear_all(t_syntax *syntax, t_token **token, t_parse *parse)
{
	clear_syntax(syntax);
	clear_token(token);
	// clear_parse(parse);
}

void	backtracking_free(t_parse **parse)
{
	if (*parse)
	{
		if (!((*parse)->token_size))
		{
			if ((*parse)->left)
			{
				free((*parse)->left);
				(*parse)->left = NULL;
			}
			if ((*parse)->right)
			{
				free((*parse)->right);
				(*parse)->right = NULL;
			}
			free((*parse));
			(*parse) = NULL;
		}
	}
}
