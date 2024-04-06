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

static t_bool	init(t_minishell *shell, char *line, char **envp);
static t_bool	lex(t_minishell *shell);

int	ms_env_exec(char *line, char **envp)
{
	t_minishell	shell;

	if (!init(&shell, line, envp))
		return (EXIT_FAILURE);
	shell.syntax.line = line;
	if (!lex(&shell))
		return (EXIT_FAILURE);
	if (!ms_parser(&(shell.ast), shell.token, shell.syntax.words_cnt))
		return (EXIT_FAILURE);
	ms_max_heredoc(shell.token);
	ms_exec(shell.ast, shell.env);
	ms_clear_all(&shell);
	ms_env_clear(shell.env);
	free(shell.env);
	return (EXIT_SUCCESS);
}

static t_bool	init(t_minishell *shell, char *line, char **envp)
{
	if (!line || !envp)
		return (FALSE);
	ft_memset(shell, 0, sizeof(t_minishell));
	shell->env = ms_env_deserialize(envp);
	if (!shell->env)
	{
		ms_puterror_cmd(NULL, "malloc");
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	lex(t_minishell *shell)
{
	t_syntax	*syntax;

	syntax = &(shell->syntax);
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
	return (TRUE);
}
