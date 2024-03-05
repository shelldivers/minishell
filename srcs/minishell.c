/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/05 14:33:46 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

size_t	is_and_or(t_parse *parse, t_token **token)
{
	size_t	i;

	i = 0;
	while (is_pipeline(token))
	{
		i += is_pipeline(token);
	}
	if (token[i] && (token[i]->type == TAND_IF || token[i]->type == TOR_IF))
	{
		i++;
		if (is_pipeline(token + i))
			i += is_pipeline(token + i);
	}
	return (i);
}

size_t	is_pipeline(t_token **token)
{
	size_t	i;

	i = 0;
	if (is_command(token))
		i += is_command(token);
	else if (is_command(token))
	{

	}
	return (i);
}

{
	size_t	i;

	i = 0;
	if (is_command(token))
		i += is_command(token);
	else if 
	return (i);
}

size_t	is_command(t_token **token)
{
	size_t	i;

	i = 0;
	if (is_simple_command(token))
		i += is_simple_command(token);
	else if (is_subshell(token))
	{
		i += is_subshell(token);
		if (is_io_redirect(token + i))
			i += is_io_redirect(token + i);
	}
	return (i);
}

size_t	is_subshell(t_token **token)
{
	if (token[0] && token[0]->type == TSUBSHELL)
		return (1);
	return (0);
}

size_t	is_simple_command(t_token **token)
{
	size_t	i;

	i = 0;
	if (is_redirect_list(token))
	{
		i += is_redirect_list(token);
		if (is_word(token + i))
		{
			i += is_word(token + i);
			if (is_cmd_suffix(token + i))
				i += is_cmd_suffix(token + i);
		}
	}
	else if (is_word(token))
	{
		i += is_word(token + i);
		if (is_cmd_suffix(token + i))
			i += is_cmd_suffix(token + i);
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

size_t	is_io_here(t_parse *parse)
{
	t_parse *new_parse;

	new_parse = new_parse(token, 2);
	if (token[0] && token[0]->type == TDLESS \
	&& token[1] && token[1]->type == TWORD)
	{
		parse->grammar = GIO_HERE;
		return (2);
	}
	return (0);
}
t_parse	*new_parse(t_token **token, size_t size)
{
	t_parse	*new_parse;

	new_parse = (t_parse *)malloc(sizeof(t_parse));
	new_parse->token = token;
	new_parse->token_size = size;
	new_parse->grammar = NULL;
	new_parse->left = NULL;
	new_parse->right = NULL;
	return (new_parse);
}

void	parser(t_parse *parse, t_token **token, size_t size)
{
	init_parse(parse, token, size);
	is_and_or(parse);
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
