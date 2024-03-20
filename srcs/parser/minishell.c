/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 14:56:53 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	parser(t_ast *ast, t_token **token, size_t size)
{
	size_t	cursor;

	ast = new_ast(token, size);
	if (!ast)
	{
		printf("invalid line\n");
		return (0);
	}
	cursor = add_ast(ast, token, ispipeline, size, LEFT);
	printf("cursor: %zu\n", cursor);
	if (cursor != size)
	{
		printf("syntax error %s\n", token[cursor]->value);
		clear_ast(ast);
		clear_token(token);
		return (0);
	}
	clear_ast(ast);
	clear_token(token);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;
	t_token		**token;
	t_ast		*ast;

	init_syntax(&syntax);
	while (1)
	{
		syntax.line = readline("minishell$ ");
		if (!(syntax.line))
			exit (1);
		lexer(&syntax);
		token = tokenize(&syntax);
		if (parser(ast, token, syntax.words_cnt))
		{
			add_history(syntax.line);
		}
		clear_syntax(&syntax);
	}
	return (0);
}
