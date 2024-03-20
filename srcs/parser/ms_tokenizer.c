/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:49:24 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 16:15:05 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "../libft/includes/libft.h"

static t_token	*ms_new_token(char *value);
static void		ms_set_tokentype(t_token **token);

t_token	**ms_tokenizer(t_syntax *syntax)
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
		exit(1);
	token->value = ft_strdup(value);
	ms_set_tokentype(&token);
	return (token);
}

static void	ms_set_tokentype(t_token **token)
{
	if (!ft_strcmp((*token)->value, "&&"))
		(*token)->type = TAND_IF;
	else if (!ft_strcmp((*token)->value, "||"))
		(*token)->type = TOR_IF;
	else if (!ft_strcmp((*token)->value, "|"))
		(*token)->type = TPIPE;
	else if (!ft_strcmp((*token)->value, "("))
		(*token)->type = TLPAREN;
	else if (!ft_strcmp((*token)->value, ")"))
		(*token)->type = TRPAREN;
	else if (!ft_strcmp((*token)->value, "<<"))
		(*token)->type = TDLESS;
	else if (!ft_strcmp((*token)->value, ">>"))
		(*token)->type = TDGREAT;
	else if (!ft_strcmp((*token)->value, "<"))
		(*token)->type = TDREAD;
	else if (!ft_strcmp((*token)->value, ">"))
		(*token)->type = TDWRITE;
	else
		(*token)->type = TWORD;
}
