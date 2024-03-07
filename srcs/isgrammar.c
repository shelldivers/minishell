/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isgrammar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/07 18:29:27 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

size_t	isand_or(t_parse *parse, t_token **token)
{
	printf ("isand_or\n");
	parse->grammar = GAND_OR;
	size_t	i;
	size_t	cursor;

	i = 1;
	cursor = 0;
	while (parse->token_size - i > 0)
	{
		if (token[parse->token_size - i]->type == TAND_IF)
		{
			parse->op = OPAND_IF;
			parse->left = ms_new_parse(token, OPNONE, parse->token_size - i);
			cursor += isand_or(parse->left, token);
			backtracking_free(&(parse->left));
			break ;
		}
		else if (token[parse->token_size - i]->type == TOR_IF)
		{
			parse->op = OPOR_IF;
			parse->left = ms_new_parse(token, OPNONE, parse->token_size - i);
			cursor += isand_or(parse->left, token);
			backtracking_free(&(parse->left));
			break ;
		}
		i++;
	}
	parse->right = ms_new_parse(token + cursor, OPNONE, i);
	cursor += ispipeline(parse->right, token);
	backtracking_free(&(parse->right));
	return (cursor);
}

size_t	ispipeline(t_parse *parse, t_token **token)
{
	printf ("ispipeline\n");
	parse->grammar = GPIPELINE;
	size_t	i;
	size_t	cursor;

	i = 1;
	cursor = 0;
	while (parse->token_size - i > 0)
	{
		if (token[parse->token_size - i]->type == TPIPE)
		{
			parse->op = OPPIPE;
			parse->left = ms_new_parse(token, OPNONE, parse->token_size - i);
			cursor += ispipeline(parse->left, token);
			backtracking_free(&(parse->left));
			break ;
		}
		i++;
	}
	parse->right = ms_new_parse(token + cursor, OPNONE, i);
	cursor += iscommand(parse->right, token);
	backtracking_free(&(parse->right));
	return (cursor);
}

size_t	iscommand(t_parse *parse, t_token **token)
{
	printf ("iscommand\n");
	parse->grammar = GCOMMAND;
	size_t	i;

	i = 0;
	parse->left = ms_new_parse(token, OPNONE, 0);
	i += issimple_command(parse->left, token);
	parse->left->token_size = i;
	backtracking_free(&(parse->left));
	if (!i)
	{
		parse->left = ms_new_parse(token, OPNONE, 0);
		i += issubshell(parse->left, token + i);
		parse->left->token_size = i;
		backtracking_free(&(parse->left));
		if (i)
		{
			parse->right = ms_new_parse(token + i, OPNONE, 0);
			i += isio_redirect(parse->right, token + i);
			parse->right->token_size = i - parse->left->token_size - 1;
			backtracking_free(&(parse->right));
		}
	}
	return (i);
}

size_t	issubshell(t_parse *parse, t_token **token)
{
	printf ("issubshell\n");
	parse->grammar = GSUBSHELL;
	if (token[0] && token[0]->type == TSUBSHELL)
	{
		parse->op = OPSUBSHELL;
		return (1);
	}
	return (0);
}
