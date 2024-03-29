/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:29:36 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/29 19:31:18 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ms_parser.h"

/**
 * separateWords - 주어진 문자열을 단어로 분리합니다.
 * 
 * @param line 단어로 분리할 문자열
 * @return void
 * @todo separate_words 를 사용한 후에는 syntax.words, syntax.line 메모리를 해제해야 합니다.
 */
void	ms_tokenizer(t_syntax *syntax)
{
	const char	*op[9] = {"&&", "||", "|", "(", ")", ">>", "<<", ">", "<"};
	size_t		i;
	size_t		start;

	if (!syntax->line)
		return ;
	syntax->words_cnt = ms_count_word(syntax->line, op, 9);
	syntax->words = (char **)malloc(sizeof(char *) * (syntax->words_cnt + 1));
	if (!syntax->words)
		return ;
	syntax->words[syntax->words_cnt] = NULL;
	i = 0;
	start = 0;
	while (i < syntax->words_cnt)
	{
		while (syntax->line[start] == ' ')
			start++;
		if (syntax->line[start] == '\0')
			break ;
		if (ms_get_op(syntax->line + start, op, 9))
			syntax->words[i] = ms_extract_token(syntax->line, &start, op, 9);
		else
			syntax->words[i] = ms_extract_word(syntax->line, &start, op, 9);
		i++;
	}
}

size_t	ms_count_word(const char *line, const char **op, size_t op_size)
{
	size_t	i;
	size_t	token_size;
	size_t	words_cnt;

	i = 0;
	words_cnt = 0;
	while (line[i])
	{
		token_size = ms_get_word(line + i, op, op_size);
		if (token_size)
			words_cnt++;
		else
		{
			token_size = ms_get_op(line + i, op, op_size);
			if (token_size)
				words_cnt++;
			else
				i++;
		}
		i += token_size;
	}
	return (words_cnt);
}
