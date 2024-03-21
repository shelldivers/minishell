/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:49:24 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/21 11:37:13 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ms_parser.h"
#include "libft.h"

static t_token		*ms_new_token(char *value);
static enum e_type	ms_get_tokentype(char *value);

t_token	**ms_lexer(t_syntax *syntax)
{
	int		i;
	t_token	**token;

	if (!syntax->words_cnt)
		return (NULL);
	token = (t_token **)malloc(sizeof(t_token *) * (syntax->words_cnt + 1));
	if (!token)
		exit (1);
	i = 0;
	while (i < syntax->words_cnt)
	{
		token[i] = ms_new_token(syntax->words[i]);
		i++;
	}
	token[i] = NULL;
	return (token);
}

static t_token	*ms_new_token(char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = ms_get_tokentype(value);
	return (token);
}

static enum e_type	ms_get_tokentype(char *value)
{
	if (!ft_strcmp(value, "&&"))
		return (TAND_IF);
	else if (!ft_strcmp(value, "||"))
		return (TOR_IF);
	else if (!ft_strcmp(value, "|"))
		return (TPIPE);
	else if (!ft_strcmp(value, "("))
		return (TLPAREN);
	else if (!ft_strcmp(value, ")"))
		return (TRPAREN);
	else if (!ft_strcmp(value, "<<"))
		return (TDLESS);
	else if (!ft_strcmp(value, ">>"))
		return (TDGREAT);
	else if (!ft_strcmp(value, "<"))
		return (TDREAD);
	else if (!ft_strcmp(value, ">"))
		return (TDWRITE);
	else
		return (TWORD);
}
