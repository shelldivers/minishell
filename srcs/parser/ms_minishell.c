/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 19:19:54 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <minishell.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	ms_parser(t_ast *ast, t_token **token, size_t size)
{
	size_t	cursor;

	ast = ms_new_ast(token, size);
	if (!ast)
	{
		// error message
		return (0);
	}
	cursor = ms_add_ast(ast, token, ms_is_pipeline, size, LEFT);
	printf ("cursor: %zu\n", cursor);
	if (cursor != size)
	{
		printf ("syntax error near unexpected token `%s'\n", token[cursor]->value);
		// error message
		ms_clear_ast(ast);
		ms_clear_token(token);
		return (0);
	}
	ms_clear_ast(ast);
	ms_clear_token(token);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;
	t_token		**token;
	t_ast		*ast;

	ms_init_syntax(&syntax);
	while (1)
	{
		syntax.line = readline("minishell$ ");
		if (!(syntax.line))
			printf ("ok\n");
		ms_tokenizer(&syntax);
		for (size_t i = 0; i < syntax.words_cnt; i++)
			printf ("syntax.words[%zu]: %s\n", i, syntax.words[i]);
		token = ms_lexer(&syntax);
		if (ms_parser(ast, token, syntax.words_cnt))
		{
			add_history(syntax.line);
		}
		ms_clear_syntax(&syntax);
	}
	return (0);
}
