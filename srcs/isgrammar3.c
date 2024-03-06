/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isgrammar3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:23 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/06 20:12:17 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

size_t	isredirect_list(t_parse *parse, t_token **token)
{
	printf ("isredirect_list\n");
	parse->grammar = GREDIRECT_LIST;
	size_t	i;

	i = 0;
	parse->left = ms_new_parse(token, OPNONE);
	i += isio_redirect(parse->left, token);
	parse->left->token_size = i;
	backtracking_free(&(parse->left));
	if (i && token[i])
		i += isredirect_list(parse->left, token + i);
	return (i);
}

size_t	isio_redirect(t_parse *parse, t_token **token)
{
	printf ("isio_redirect\n");
	parse->grammar = GIO_REDIRECT;
	size_t	i;

	i = 0;
	parse->left = ms_new_parse(token, OPNONE);
	i += isio_file(parse->left, token);
	parse->left->token_size = i;
	backtracking_free(&(parse->left));
	if (!i)
	{
		parse->left = ms_new_parse(token, OPNONE);
		i += isio_here(parse->left, token);
		parse->left->token_size = i;
		backtracking_free(&(parse->left));
	}
	return (i);
}

size_t	isio_file(t_parse *parse, t_token **token)
{
	printf("isio_file\n");
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

size_t	isio_here(t_parse *parse, t_token **token)
{
	printf ("isio_here\n");
	parse->grammar = GIO_HERE;
	if (token[0] && token[0]->type == TDLESS \
	&& token[1] && token[1]->type == TWORD)
	{
		parse->op = OPIO_HERE;
		return (2);
	}
	return (0);
}
