/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/03 17:00:19 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ms_minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	ms_clear_all(t_syntax *syntax, t_token **token, t_ast *ast)
{
	ms_clear_syntax(syntax);
	ms_clear_token(token);
	ms_clear_ast(ast);
}


int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;
	t_token		**token;
	t_env		**env;
	t_ast		*ast;

	if (argc != 1 || !argv || !envp)
		return (1);
	ms_init_syntax(&syntax);
	env = ms_env_deserialize(envp);
	ast = NULL;
	while (1)
	{
		syntax.line = readline("minishell$ ");
		if (!syntax.line)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		add_history(syntax.line);
		ms_tokenizer(&syntax);
		token = ms_lexer(&syntax);
		ms_parser(&ast, token, syntax.words_cnt);
		ms_exec(ast, env);
		ms_clear_all(&syntax, token, ast);
	}
	return (0);
}
