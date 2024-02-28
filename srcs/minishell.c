/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/02/28 17:25:22 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	parser(t_token **token)
{
	int			i;
	t_parser	parser;

	i = 0;
	while (token[i])
	{
		if (token[i]->type == PIPE)
		{
			
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;
	t_token		**token;

	atexit(leaks);
	init_syntax(&syntax);
	while (1)
	{
		syntax.line = readline("minishell$ ");
		if (!syntax.line)
			break ;
		add_history(syntax.line);
		lexer(&syntax);
		token = tokenize(&syntax);
		parser(token);
		clear_token(token);
		clear_syntax(&syntax);
	}
	return (0);
}
