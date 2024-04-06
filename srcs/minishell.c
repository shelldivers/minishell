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

#include "ft_printf.h"
#include "libft.h"
#include "ms_error.h"
#include "ms_exec.h"
#include "ms_minishell.h"
#include "ms_signal.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

static void		init(t_minishell *shell, int argc, char **argv, char **envp);
static void		prompt(t_syntax *syntax);
static t_bool	lex(t_minishell *shell);
static t_bool	set_shlvl(t_env **env);

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	init(&shell, argc, argv, envp);
	while (1)
	{
		ms_clear_all(&shell);
		prompt(&(shell.syntax));
		if (!lex(&shell))
			continue ;
		if (!ms_parser(&(shell.ast), shell.token, shell.syntax.words_cnt))
			continue ;
		ms_max_heredoc(shell.token);
		ms_exec(shell.ast, shell.env);
	}
}

static void	init(t_minishell *shell, int argc, char **argv, char **envp)
{
	if (argc != 1 || !argv || !envp)
		exit(EXIT_FAILURE);
	ft_memset(shell, 0, sizeof(t_minishell));
	shell->env = ms_env_deserialize(envp);
	if (!shell->env || !set_shlvl(shell->env))
	{
		ms_puterror_cmd(NULL, "malloc");
		exit(EXIT_FAILURE);
	}
	ms_set_signal_prompt();
}

static void	prompt(t_syntax *syntax)
{
	syntax->line = readline("minishell$ ");
	if (!syntax->line)
	{
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	add_history(syntax->line);
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

static t_bool	set_shlvl(t_env **env)
{
	char	*shlvl;
	char	*nextlvl;
	int		lvl;
	t_bool	result;

	shlvl = getenv(SHLVL);
	if (!shlvl)
		lvl = 1;
	else
		lvl = ft_atoi(shlvl) + 1;
	if (lvl < 0)
		lvl = 0;
	nextlvl = ft_sprintf("%d", lvl);
	if (!nextlvl)
		return (FALSE);
	result = ms_setenv(env, SHLVL, nextlvl);
	free(nextlvl);
	if (!result)
		return (FALSE);
	return (TRUE);
}
