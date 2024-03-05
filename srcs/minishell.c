/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/05 19:25:02 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

size_t	isand_or(t_parse *parse, t_token **token)
{
	size_t	i;

	i = 0;
	i += ispipeline(parse, token);
	if (token[i] && token[i]->type == TAND_IF)
	{
		i++;
		if (is_and_or(parse, token + i))
			i += is_and_or(parse, token + i);
	}
	else if (token[i] && token[i]->type == TOR_IF)
	{
		i++;
		if (is_and_or(parse, token + i))
			i += is_and_or(parse, token + i);
	}
	return (i);
}

size_t	ispipeline(t_parse *parse, t_token **token)
{
	size_t	i;

	i = 0;
	i += iscommand(parse, token);
	if (token[i] && token[i]->type == TPIPE)
	{
		i++;
		if (is_pipeline(parse, token + i))
			i += is_pipeline(parse, token + i);
	}
	return (i);
}

size_t	iscommand(t_parse *parse, t_token **token)
{
	size_t	i;

	i = 0;
	i += issimple_command(parse, token);
	if (!i)
		i += issubshell(parse, token + i);
	if (i)
		i += isio_redirect(parse, token + i);
	return (i);
}

size_t	issubshell(t_parse *parse, t_token **token)
{
	if (token[0] && token[0]->type == TSUBSHELL)
		return (1);
	return (0);
}

size_t	issimple_command(t_parse *parse, t_token **token)
{
	size_t	i;

	i = 0;
	i += is_redirect_list(token);
	if (i)
	{
		if (token[i] && token[i]->type == TWORD)
		{
			i++;
			i += is_cmd_suffix(token + i);
		}
	}
	return (i);
}

size_t	iscmd_suffix(t_parse *parse, t_token **token)
{
	size_t	i;

	i = 0;
	i += is_redirect_list(token);
	if (!i)
	{
		i += is_word(token);
		if (i)
			i += is_cmd_suffix(token + i);
	}
	return (i);
}

size_t	isredirect_list(t_parse *parse, t_token **token)
{
	size_t	i;

	i = 0;
	i += isio_redirect(parse, token);
	if (i)
		i += isredirect_list(parse, token + i);
	return (i);
}

size_t	isio_redirect(t_parse *parse, t_token **token)
{
	size_t	i;

	i = 0;
	i += isio_file(parse, token);
	if (!i)
		i += isio_here(parse, token);
	return (i);
}

size_t	isio_file(t_parse *parse, t_token **token)
{
	t_parse	*new_parse;

	new_parse = ms_new_parse(token, 2);
	if (token[0] && (token[0]->type == TDREAD \
	|| token[0]->type == TDWRITE \
	|| token[0]->type == TDGREAT) \
	&& token[1] && token[1]->type == TWORD)
	{
		parse->left = new_parse;
		new_parse->op = OPIO_FILE;
		return (2);
	}
	return (0);
}

size_t	isio_here(t_parse *parse, t_token **token)
{
	t_parse	*new_parse;

	new_parse = ms_new_parse(token, 2);
	if (token[0] && token[0]->type == TDLESS \
	&& token[1] && token[1]->type == TWORD)
	{
		parse->left = new_parse;
		new_parse->op = OPIO_HERE;
		return (2);
	}
	return (0);
}
t_parse	*ms_new_parse(t_token **token, size_t size)
{
	t_parse	*new_parse;

	new_parse = (t_parse *)malloc(sizeof(t_parse));
	new_parse->token = token;
	new_parse->token_size = size;
	new_parse->op = OPNONE;
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
