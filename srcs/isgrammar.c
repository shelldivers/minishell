/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isgrammar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/06 20:13:59 by jiwojung         ###   ########.fr       */
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

	i = 0;
	parse->left = ms_new_parse(token, OPNONE);
	i += ispipeline(parse->left, token);
	parse->left->token_size = i;
	backtracking_free(&(parse->left));
	if (i && token[i] && token[i + 1] && token[i]->type == TAND_IF)
	{
		parse->op = OPAND_IF;
		i++;
		parse->right = ms_new_parse(token + i, OPNONE);
		i += isand_or(parse->right, token + i);
		parse->right->token_size = i - parse->left->token_size - 1;
		backtracking_free(&(parse->right));
	}
	else if (i && token[i] && token[i + 1] && token[i]->type == TOR_IF)
	{
		parse->op = OPOR_IF;
		i++;
		parse->right = ms_new_parse(token + i, OPNONE);
		i += isand_or(parse->right, token + i);
		parse->right->token_size = i - parse->left->token_size - 1;
		backtracking_free(&(parse->right));
	}
	return (i);
}

size_t	ispipeline(t_parse *parse, t_token **token)
{
	printf ("ispipeline\n");
	parse->grammar = GPIPELINE;
	size_t	i;

	i = 0;
	parse->left = ms_new_parse(token, OPNONE);
	i += iscommand(parse->left, token);
	parse->left->token_size = i;
	backtracking_free(&(parse->left));
	if (i && token[i] && token[i + 1] && token[i]->type == TPIPE)
	{
		parse->op = OPPIPE;
		i++;
		parse->right = ms_new_parse(token + i, OPNONE);
		i += ispipeline(parse->right, token + i);
		parse->right->token_size = i - parse->left->token_size - 1;
		backtracking_free(&(parse->right));
	}
	return (i);
}

size_t	iscommand(t_parse *parse, t_token **token)
{
	printf ("iscommand\n");
	parse->grammar = GCOMMAND;
	size_t	i;

	i = 0;
	parse->left = ms_new_parse(token, OPNONE);
	i += issimple_command(parse->left, token);
	parse->left->token_size = i;
	backtracking_free(&(parse->left));
	if (!i)
	{
		parse->left = ms_new_parse(token, OPNONE);
		i += issubshell(parse->left, token + i);
		parse->left->token_size = i;
		backtracking_free(&(parse->left));
		if (i)
		{
			parse->right = ms_new_parse(token + i, OPNONE);
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
