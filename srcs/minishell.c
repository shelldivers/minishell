/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/21 10:25:31 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ms_parser.h"

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;
	t_token		**token;
	t_ast		*ast;

	ms_init_syntax(&syntax);
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
			}
			ms_clear_syntax(&syntax);
		}
	}
	return (0);
}
