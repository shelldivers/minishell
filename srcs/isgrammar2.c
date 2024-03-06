/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isgrammar2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/06 20:46:51 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

size_t	isword(t_parse *parse, t_token **token)
{
	printf("isword\n");
	parse->grammar = GWORD;
	if (token[0] && token[0]->type == TWORD)
	{
		return (1);
	}
	return (0);
}

size_t	issimple_command(t_parse *parse, t_token **token)
{
	printf("issimple_command\n");
	parse->grammar = GSIMPLE_COMMAND;
	size_t	i;

	i = 0;
	parse->left = ms_new_parse(token, OPNONE);
	i += isredirect_list(parse->left, token);
	parse->left->token_size = i;
	backtracking_free(&(parse->left));
	if (i && token[i] && token[i]->type == TWORD)
	{
		parse->left = ms_new_parse(token + i, OPNONE);
		i += isword(parse->left, token + i);
		parse->left->token_size = i;
		parse->right = ms_new_parse(token + i, OPNONE);
		i += iscmd_suffix(parse->right, token + i);
		parse->right->token_size = i - parse->left->token_size;
		backtracking_free(&(parse->right));
	}
	else if (!i && token[i] && token[i]->type == TWORD)
	{
		parse->left = ms_new_parse(token + i, OPNONE);
		i += isword(parse->left, token + i);
		parse->left->token_size = i;
		parse->right = ms_new_parse(token + i, OPNONE);
		i += iscmd_suffix(parse->right, token + i);
		parse->right->token_size = i - parse->left->token_size;
		backtracking_free(&(parse->right));
	}
	return (i);
}

size_t	iscmd_suffix(t_parse *parse, t_token **token)
{
	printf("iscmd_suffix\n");
	parse->grammar = GCMD_SUFFIX;
	size_t	i;

	i = 0;
	parse->left = ms_new_parse(token, OPNONE);
	i += isredirect_list(parse->left, token);
	parse->left->token_size = i;
	backtracking_free(&(parse->left));
	if (!i && token[i] && token[i]->type == TWORD)
	{
		parse->left = ms_new_parse(token + i, OPNONE);
		i += isword(parse->left, token + i);
		parse->left->token_size = i;
		parse->right = ms_new_parse(token + i, OPNONE);
		i += iscmd_suffix(parse->right, token + i);
		parse->right->token_size = i;
		backtracking_free(&(parse->right));
	}
	return (i);
}
