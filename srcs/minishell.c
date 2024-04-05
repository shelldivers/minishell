/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 17:11:14 by jiwojung         ###   ########.fr       */
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
	ft_memset(&shell, 0, sizeof(t_minishell));
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
		if (!shell.syntax.words_cnt)
			continue ;
		shell.token = ms_lexer(&shell.syntax);
		if (!shell.token)
		{
			ms_clear_all(&shell.syntax, shell.token, shell.ast);
			ms_puterror_cmd(NULL, "malloc");
			continue ;
		}
		ms_parser(&shell.ast, shell.token, shell.syntax.words_cnt);
		ms_max_heredoc(shell.token);
		ms_exec(shell.ast, shell.env);
		ms_clear_all(&shell.syntax, shell.token, shell.ast);
	}
}
