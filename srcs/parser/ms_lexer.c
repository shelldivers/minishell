/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:49:24 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/21 15:00:34 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_parser.h"
#include <stdio.h>
#include <stdlib.h>

static t_token		*ms_new_token(char *value);
static enum e_type	ms_get_tokentype(char *value);

/**
 * @errno ENOMEM
 */
t_token	**ms_lexer(t_syntax *syntax)
{
	int		i;
	t_token	**token;

	token = (t_token **)malloc(sizeof(t_token *) * (syntax->words_cnt + 1));
	if (!token)
		return (NULL);
	i = 0;
	while (i < syntax->words_cnt)
	{
		token[i] = ms_new_token(syntax->words[i]);
		if (!token[i])
		{
			ms_clear_token(token);
			return (NULL);
		}
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
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
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
