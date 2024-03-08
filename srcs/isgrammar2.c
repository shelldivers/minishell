/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isgrammar2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/08 16:09:28 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

//terminal
size_t	isword(t_parse *parse, t_token **token)
{
	if (parse->token_size != 1)
		return (0);
	printf("isword\n");
	for (size_t j = 0; j < parse->token_size; j++)
	{
		printf("%s ", token[j]->value);
	}
	parse->grammar = GWORD;
	if (token[0] && token[0]->type == TWORD)
	{
		return (1);
	}
	return (0);
}

//terminal
size_t	iscmd_word(t_parse *parse, t_token **token)
{
	if (parse->token_size != 1)
		return (0);
	printf("iscmd_word\n");
	for (size_t j = 0; j < parse->token_size; j++)
	{
		printf("%s ", token[j]->value);
	}
	parse->grammar = GCMD_WORD;
	if (token[0] && token[0]->type == TWORD)
	{
		parse->op = OPCMD_WORD;
		return (1);
	}
	return (0);
}

//unterminal
size_t	issimple_command(t_parse *parse, t_token **token)
{
	size_t	i;
	size_t	cursor;

	if (parse->token_size == 0)
		return (0);
	printf("issimple_command\n");
	for (size_t j = 0; j < parse->token_size; j++)
	{
		printf("%s ", token[j]->value);
	}
	printf ("\n");
	parse->grammar = GSIMPLE_COMMAND;
	i = 1;
	cursor = 0;
	cursor += add_parse(parse, token, parse->token_size, \
	iscmd_prefix, LEFT);
	if (cursor)
	{
		cursor += add_parse(parse, token + cursor, parse->token_size - cursor, \
		iscmd_word, LEFT);
	}
	else
	{
		cursor += add_parse(parse, token, 1, \
		iscmd_word, LEFT);
		cursor += add_parse(parse, token + cursor, parse->token_size - cursor, \
		iscmd_suffix, LEFT);
	}
	return (cursor);
}

//unterminal
size_t	iscmd_suffix(t_parse *parse, t_token **token)
{
	size_t	size;
	size_t	cursor;

	if (parse->token_size == 0)
		return (0);
	printf("iscmd_suffix\n");
	for (size_t j = 0; j < parse->token_size; j++)
	{
		printf("%s ", token[j]->value);
	}
	printf ("\n");
	parse->grammar = GCMD_SUFFIX;
	size = 0;
	cursor = 0;
	if (token[size] && token[size]->type == TWORD)
	{
		if (size - 1 >= 0 && (token[size - 1]->type == TDREAD \
		|| token[size - 1]->type == TDWRITE \
		|| token[size - 1]->type == TDGREAT \
		|| token[size - 1]->type == TDLESS))
		{
			cursor += add_parse(parse, token + size - 1, 2, \
			isio_redirect, RIGHT);
			cursor += add_parse(parse, token, size - 1, \
			iscmd_suffix, LEFT);
		}
	}
	return (cursor);
}

size_t	iscmd_prefix(t_parse *parse, t_token **token)
{
	size_t	size;
	size_t	cursor;

	if (parse->token_size < 2)
		return (0);
	printf("iscmd_prefix\n");
	for (size_t j = 0; j < parse->token_size; j++)
	{
		printf("%s ", token[j]->value);
	}
	printf ("\n");
	parse->grammar = GCMD_PREFIX;
	size = parse->token_size - 1;
	cursor = 0;
	if (parse->token_size > 1)
	{
		cursor += add_parse(parse, token + size - 1, 2, \
		isio_redirect, RIGHT);
		if (cursor)
		{
			cursor += add_parse(parse, token + size, 1, \
			iscmd_prefix, LEFT);
		}
		else
		{
			cursor += add_parse(parse, token + size, 1, \
			isword, LEFT);
			cursor += add_parse(parse, token, size, \
			iscmd_prefix, LEFT);
		}
	}
	return (cursor);
}
