/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/02/28 19:18:56 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

size_t	define_bygrammar(t_token **token, size_t start, size_t end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (token[i]->type == PIPE)
			return (PIPE);
		i++;
	}
}

void	parser(t_token **token, size_t start, size_t end)
{
	int			i;
	t_parser	parser;

	i = start;
	while (i < end)
	{
		if (token[i]->type == PIPE)
		{
			add_parser_tree(&parser, token[i]);
			parser(token, start, i);
			parser(token, i + 1, end);
		}
		else if (token[i]->type == DLESS || token[i]->type == DGREAT \
		|| token[i]->type == DREAD || token[i]->DWRITE == LESS)
		{
			add_parser_tree(&parser, token[i]);
			parser(token, start, i);
			parser(token, i + 1, end);
		}
		else if (token[i]->type == WORD)
		{
			add_parser_tree(&parser, token[i]);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;
	t_token		**token;

	init_syntax(&syntax);
	while (1)
	{
		syntax.line = readline("minishell$ ");
		if (!syntax.line)
			break ;
		add_history(syntax.line);
		lexer(&syntax);
		token = tokenize(&syntax);
		parser(token, 0, syntax.words_cnt);
		clear_token(token);
		clear_syntax(&syntax);
	}
	return (0);
}
