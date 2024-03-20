/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:29:36 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 14:29:57 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "../libft/includes/libft.h"

/**
 * separateWords - 주어진 문자열을 단어로 분리합니다.
 * 
 * @param line 단어로 분리할 문자열
 * @return void
 * @todo separate_words 를 사용한 후에는 syntax.words, syntax.line 메모리를 해제해야 합니다.
 */
void	lexer(t_syntax *syntax)
{
	const char	*op[9] = {"&&", "||", "|", "(", ")", ">>", "<<", ">", "<"};
	size_t		i;
	size_t		start;

	syntax->words_cnt = count_word(syntax->line, op);
	syntax->words = (char **)malloc(sizeof(char *) * (syntax->words_cnt + 1));
	if (!syntax->words)
		exit(EXIT_FAILURE);
	syntax->words[syntax->words_cnt] = NULL;
	i = 0;
	start = 0;
	while (i < syntax->words_cnt)
	{
		while (syntax->line[start] == ' ')
			start++;
		if (syntax->line[start] == '\0')
			break ;
		if (get_op(syntax->line + start, op))
			syntax->words[i] = extract_token(syntax->line, &start, op);
		else
			syntax->words[i] = extract_word(syntax->line, &start, op);
		i++;
	}
	i = 0;
}

size_t	count_word(const char *line, const char **op)
{
	size_t	i;
	size_t	token_size;
	size_t	words_cnt;

	i = 0;
	words_cnt = 0;
	while (line[i])
	{
		token_size = get_word(line + i, op);
		if (token_size)
			words_cnt++;
		else
		{
			token_size = get_op(line + i, op);
			if (token_size)
				words_cnt++;
			else
				i++;
		}
		i += token_size;
	}
	return (words_cnt);
}

size_t	get_op(const char *s1, const char **op)
{
	size_t	i;
	size_t	op_size;

	i = 0;
	while (i < 9)
	{
		op_size = ft_strlen(op[i]);
		if (ft_strncmp(s1, op[i], op_size) == 0)
			return (op_size);
		i++;
	}
	return (0);
}

size_t	get_word(const char *line, const char **op)
{
	size_t	i;

	i = 0;
	while (line[i] != ' ' && line[i] != '\0' && get_op(line + i, op) == 0)
	{
		if (line[i] == '\'' || line[i] == '"')
			i += close_quote(line + i, line[i]);
		else
			i++;
	}
	return (i);
}

size_t	close_quote(const char *line, const char quote)
{
	size_t	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == quote)
			return (i + 1);
		i++;
	}
	return (1);
}
