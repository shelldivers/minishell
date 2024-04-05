/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 20:53:09 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_error.h"
#include "ms_exec.h"
#include "ms_minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static t_bool	parse(t_minishell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	if (argc != 1 || !argv || !envp)
		return (1);
	ft_memset(&shell, 0, sizeof(t_minishell));
	shell.env = ms_env_deserialize(envp);
	while (1)
	{
		shell.syntax.line = readline("minishell$ ");
		if (!shell.syntax.line)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		add_history(shell.syntax.line);
		if (parse(&shell))
			ms_exec(shell.ast, shell.env);
		ms_clear_all(&shell);
	}
}

static t_bool	parse(t_minishell *shell)
{
	t_syntax	*syntax;
	t_ast		**ast;

	syntax = &(shell->syntax);
	ast = &(shell->ast);
	if (!ms_tokenizer(syntax))
	{
		ms_puterror_cmd(NULL, "malloc");
		return (FALSE);
	}
	if (!syntax->words_cnt)
		return (FALSE);
	shell->token = ms_lexer(syntax);
	if (!shell->token)
	{
		ms_puterror_cmd(NULL, "malloc");
		return (FALSE);
	}
	if (!ms_parser(ast, shell->token, syntax->words_cnt))
		return (FALSE);
	ms_max_heredoc(shell->token);
	return (TRUE);
}
