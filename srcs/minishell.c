/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/22 17:56:24 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;
	t_token		**token;
	t_ast		*ast;
	int			exit_code;

	if (argc != 1 || !argv || !envp)
		return (1);
	ms_init_syntax(&syntax);
	ast = NULL;
	while (1)
	{
		syntax.line = readline("minishell$ ");
		if (syntax.line)
			add_history(syntax.line);
		ms_tokenizer(&syntax);
		token = ms_lexer(&syntax);
		ms_parser(&ast, token, syntax.words_cnt);
		exit_code = 0;
		for (size_t i = 0; i < syntax.words_cnt; i++)
			printf ("syntax.words[%zu]: %s\n", i, syntax.words[i]);
		int pid = fork();
		if (pid == 0)
		{
			if (execve(syntax.words[0], syntax.words, envp) == -1)
				printf ("execve error\n");
		}
		else
			waitpid(pid, &exit_code, 0);
		ms_clear_syntax(&syntax);
		ms_clear_token(token);
		ms_clear_ast(ast);
	}
	return (0);
}
