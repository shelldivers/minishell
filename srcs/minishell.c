/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/04 15:21:04 by jiwojung         ###   ########.fr       */
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
	t_minishell	shell;

	if (argc != 1 || !argv || !envp)
		return (1);
	ms_init_syntax(&shell.syntax);
	shell.env = ms_env_deserialize(envp);
	shell.ast = NULL;
	while (1)
	{
		shell.syntax.line = readline("minishell$ ");
		if (!shell.syntax.line)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		add_history(shell.syntax.line);
		ms_tokenizer(&shell.syntax);
		shell.token = ms_lexer(&shell.syntax);
		ms_parser(&shell.ast, shell.token, shell.syntax.words_cnt);
		ms_max_heredoc(shell.token);
		ms_exec(shell.ast, shell.env);
		ms_clear_all(&shell.syntax, shell.token, shell.ast);
	}
	return (0);
}
