/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isgrammar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/08 16:12:25 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

//unterminal
size_t	isand_or(t_parse *parse, t_token **token)
{
	size_t	i;
	size_t	cursor;

	if (parse->token_size == 0)
		return (0);
	printf ("isand_or\n");
	for (size_t j = 0; j < parse->token_size; j++)
	{
		printf("%s ", token[j]->value);
	}
	printf ("\n");
	parse->grammar = GAND_OR;
	i = 1;
	cursor = 0;
	while (parse->token_size - i)
	{
		if (token[parse->token_size - i]->type == TAND_IF)
		{
			parse->op = OPAND_IF;
			cursor += add_parse(parse, token, parse->token_size - i, \
			isand_or, LEFT);
			break ;
		}
		else if (token[parse->token_size - i]->type == TOR_IF)
		{
			parse->op = OPOR_IF;
			cursor += add_parse(parse, token, parse->token_size - i, \
			isand_or, LEFT);
			break ;
		}
		i++;
	}
	cursor += add_parse(parse, token + cursor, i, \
	ispipeline, RIGHT);
	return (cursor);     
}

//unterminal
size_t	ispipeline(t_parse *parse, t_token **token)
{
	size_t	i;
	size_t	cursor;

	if (parse->token_size == 0)
		return (0);
	printf ("ispipeline\n");
	for (size_t j = 0; j < parse->token_size; j++)
	{
		printf("%s ", token[j]->value);
	}
	printf ("\n");
	parse->grammar = GPIPELINE;
	i = 1;
	cursor = 0;
	while (parse->token_size - i)
	{
		if (token[parse->token_size - i]->type == TPIPE)
		{
			parse->op = OPPIPE;
			cursor += add_parse(parse, token, parse->token_size - i, \
			ispipeline, LEFT);
			break ;
		}
		i++;
	}
	if (!cursor)
		cursor += add_parse(parse, token, parse->token_size, \
		iscommand, LEFT);
	else
		cursor += add_parse(parse, token + cursor, i, \
		iscommand, RIGHT);
	return (cursor);
}

size_t	iscommand(t_parse *parse, t_token **token)
{
	size_t	i;
	size_t	cursor;

	if (parse->token_size == 0)
		return (0);
	printf ("iscommand\n");
	for (size_t j = 0; j < parse->token_size; j++)
	{
		printf("%s ", token[j]->value);
	}
	printf ("\n");
	parse->grammar = GCOMMAND;
	i = 0;
	cursor = 0;
	if (token[0] && token[0]->type == TSUBSHELL)
	{
		cursor += add_parse(parse, token, 1, \
		issubshell, LEFT);
		cursor += add_parse(parse, token + cursor, parse->token_size - cursor, \
		isio_redirect, RIGHT);
	}
	else
		cursor += add_parse(parse, token, 1, \
		issimple_command, LEFT);
	return (cursor);
}

//terminal
size_t	issubshell(t_parse *parse, t_token **token)
{
	if (parse->token_size == 0)
		return (0);
	for (size_t j = 0; j < parse->token_size; j++)
	{
		printf("%s ", token[j]->value);
	}
	printf ("\n");
	printf ("issubshell\n");
	parse->grammar = GSUBSHELL;
	if (token[0] && token[0]->type == TSUBSHELL)
	{
		parse->op = OPSUBSHELL;
		return (1);
	}
	return (0);
}
