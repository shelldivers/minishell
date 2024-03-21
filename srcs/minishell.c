/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/21 16:55:49 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	main(void)
{
	t_syntax	syntax;
	t_token		**token;
	t_ast		*ast;

	ms_init_syntax(&syntax);
	ast = NULL;
	while (1)
	{
		syntax.line = readline("minishell$ ");
		if (syntax.line)
		{
			ms_tokenizer(&syntax);
			token = ms_lexer(&syntax);
			if (ms_parser(ast, token, syntax.words_cnt))
			{
				add_history(syntax.line);
				ms_exec(ast);
			}
			ms_clear_ast(ast);
			ms_clear_token(token);
			ms_clear_syntax(&syntax);
		}
	}
	return (0);
}
