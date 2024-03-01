/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:44:20 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/01 16:31:30 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	init_syntax(t_syntax *syntax)
{
	syntax->line = NULL;
	syntax->words = NULL;
	syntax->words_cnt = 0;
}

void	init_parse(t_parser **parser, t_token **token, size_t size)
{
	parser = (t_parser *)malloc(sizeof(t_parser));
	if (!parser)
		exit (1);
	parser->grammar = GNONE;
	parser->token = token;
	parser->token_size = size;
	parser->left = NULL;
	parser->right = NULL;
}

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
	}
	syntax->words_cnt = 0;
}

void	clear_parse_tree(t_parse_tree *parser_head)
{
	if (parser_head)
	{
		clear_parse_tree(parser_head->left);
		clear_parse_tree(parser_head->right);
		free(parser_head);
	}
}

void	clear_all(t_syntax *syntax, t_token **token, t_parse_tree *parser_head)
{
	clear_syntax(syntax);
	clear_token(token);
	clear_parse_tree(parser_head);
}
