/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/04 18:50:57 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

size_t	is_simple_command(t_token **token)
{
	size_t	i;

	i = 0;
	if (is_redirect_list(token))
	{
		i += is_redirect_list(token);
		token += i;
	}
	return (i);

}

size_t	is_word(t_token **token)
{
	if (token[0] && token[0]->type == TWORD)
		return (1);
	return (0);
}

size_t	is_cmd_suffix(t_token **token)
{
	size_t	i;

	i = 0;
	if (is_redirect_list(token))
	{
		i += is_redirect_list(token);
		token += i;
	}
	else if (is_word(token))
	{
		while (is_word(token + i))
			i += is_word(token + i);
	}
	return (i);
}

size_t	is_redirect_list(t_token **token)
{
	size_t	i;

	i = 0;
	while (is_io_redirect(token))
		i += is_io_redirect(token + i);
	return (i);
}

size_t	is_io_redirect(t_token **token)
{
	size_t	i;

	i = 0;
	if (is_io_file(token) || is_io_here(token))
		return (2);
	return (0);
}

size_t	is_io_file(t_token **token)
{
	if (token[0] && (token[0]->type == TDREAD \
	|| token[0]->type == TDWRITE \
	|| token[0]->type == TDGREAT) \
	&& token[1] && token[1]->type == TWORD)
		return (2);
	return (0);
}

size_t	is_io_here(t_token **token)
{
	if (token[0] && token[0]->type == TDLESS \
	&& token[1] && token[1]->type == TWORD)
		return (2);
	return (0);
}

void	parser(t_parse *parse, t_token **token, size_t size)
{
	init_parse(parse, token, size);
	isand_or(parse);
}

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;
	t_token		**token;
	t_parse		*parse;

	init_syntax(&syntax);
	while (1)
	{
		parse = NULL;
		syntax.line = readline("minishell$ ");
		if (!(syntax.line))
			exit (1);
		add_history(syntax.line);
		lexer(&syntax);
		token = tokenize(&syntax);
		parser(parse, token, syntax.words_cnt);
		execute_tree(parse);
		clear_all(&syntax, token, parse);
	}
	return (0);
}
