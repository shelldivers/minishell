/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:29:36 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 20:58:36 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bool.h"
#include "ms_exec.h"
#include "ms_parser.h"
#include <stdio.h>
#include <stdlib.h>

static t_bool	ms_extract(t_syntax *syntax, int *start, int idx);

t_bool	ms_tokenizer(t_syntax *syntax)
{
	int			i;
	int			start;
	const char	*op[OP_SIZE] = {
		"&&", "||", "|", "(",
		")", ">>", "<<", ">", "<"
	};

	syntax->words_cnt = ms_count_word(syntax->line, op);
	syntax->words = (char **)malloc(sizeof(char *) * (syntax->words_cnt + 1));
	if (!syntax->words)
		return (FALSE);
	i = 0;
	start = 0;
	while (i < syntax->words_cnt)
	{
		while (syntax->line[start] == ' ')
			start++;
		if (syntax->line[start] == '\0')
			break ;
		if (!ms_extract(syntax, &start, i))
			return (FALSE);
		i++;
	}
	syntax->words[i] = NULL;
	return (TRUE);
}

int	ms_count_word(const char *line, const char **op)
{
	int	i;
	int	token_size;
	int	words_cnt;

	i = 0;
	words_cnt = 0;
	while (line[i])
	{
		token_size = ms_get_word(line + i, op);
		if (token_size)
			words_cnt++;
		else
		{
			token_size = ms_get_op(line + i, op);
			if (token_size)
				words_cnt++;
			else
				i++;
		}
		i += token_size;
	}
	return (words_cnt);
}

static t_bool	ms_extract(t_syntax *syntax, int *start, int idx)
{
	const char	*op[OP_SIZE] = {
		"&&", "||", "|", "(",
		")", ">>", "<<", ">", "<"
	};

	if (ms_get_op(syntax->line + *start, op))
		syntax->words[idx] = ms_extract_token(syntax->line, start, op);
	else
		syntax->words[idx] = ms_extract_word(syntax->line, start, op);
	if (!syntax->words[idx])
	{
		ms_clear_sec_dimentional(syntax->words);
		return (FALSE);
	}
	return (TRUE);
}
