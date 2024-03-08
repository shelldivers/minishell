/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isgrammar3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/08 15:34:06 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

//unterminal
size_t	isio_redirect(t_parse *parse, t_token **token)
{
	size_t	i;
	size_t	cursor;

	if (parse->token_size != 2)
		return (0);
	printf ("isio_redirect\n");
	for (size_t j = 0; j < parse->token_size; j++)
	{
		printf("%s ", token[j]->value);
	}
	printf ("\n");
	parse->grammar = GIO_REDIRECT;
	i = 0;
	cursor = 0;
	if (token[0] && (token[0]->type == TDREAD \
	|| token[0]->type == TDWRITE \
	|| token[0]->type == TDGREAT) \
	&& token[1] && token[1]->type == TWORD)
	{
		add_parse(parse, token, 2, isio_file, LEFT);
		return (2);
	}
	else if (token[0] && token[0]->type == TDLESS \
	&& token[1] && token[1]->type == TWORD)
	{
		add_parse(parse, token, 2, isio_here, LEFT);
	}
	return (cursor);
}

//terminal
size_t	isio_file(t_parse *parse, t_token **token)
{
	if (parse->token_size != 2)
		return (0);
	printf("isio_file\n");
	for (size_t j = 0; j < parse->token_size; j++)
	{
		printf("%s ", token[j]->value);
	}
	printf ("\n");
	parse->grammar = GIO_FILE;
	if (token[0] && (token[0]->type == TDREAD \
	|| token[0]->type == TDWRITE \
	|| token[0]->type == TDGREAT) \
	&& token[1] && token[1]->type == TWORD)
	{
		parse->op = OPIO_FILE;
		return (2);
	}
	return (0);
}

//terminal
size_t	isio_here(t_parse *parse, t_token **token)
{
	if (parse->token_size != 2)
		return (0);
	printf ("isio_here\n");
	for (size_t j = 0; j < parse->token_size; j++)
	{
		printf("%s ", token[j]->value);
	}
	printf ("\n");
	parse->grammar = GIO_HERE;
	if (token[0] && token[0]->type == TDLESS \
	&& token[1] && token[1]->type == TWORD)
	{
		parse->op = OPIO_HERE;
		return (2);
	}
	return (0);
}
