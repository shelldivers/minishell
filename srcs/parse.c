/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/02/26 19:19:12 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	init_syntax(t_syntax *syntax)
{
	syntax->line = NULL;
	syntax->words = NULL;
	syntax->words_cnt = 0;
}

void	clear_syntax(t_syntax *syntax)
{
	if (syntax->line)
		free(syntax->line);
	if (syntax->words)
	{
		while (syntax->words_cnt--)
			free(syntax->words[syntax->words_cnt]);
		free(syntax->words);
	}
	syntax->words_cnt = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;

	init_syntax(&syntax);
	while (1)
	{
		syntax.line = readline("minishell$ ");
		if (!syntax.line)
			break ;
		add_history(syntax.line);
		separate_words(&syntax);
		clear_syntax(&syntax);
	}
	return (0);
}
