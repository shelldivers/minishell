/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:29:36 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/17 15:49:02 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

static size_t	count_word(const char *line, const char **op);
static size_t	get_op(const char *s1, const char **op);
static size_t	get_word(const char *line, const char **op);
static size_t	close_quote(const char *line, const char quote);
static char		*extract_word(char *line, size_t *start, const char **op);
static char		*extract_token(char *line, size_t *start, const char **op);

/*==================LIBFT_START===========================*/

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (s[cnt] != '\0')
		cnt++;
	return (cnt);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_;
	const unsigned char	*src_;
	size_t				i;

	if (dst == 0 && src == 0)
		return (0);
	dst_ = (unsigned char *)dst;
	src_ = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_[i] = src_[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!str)
		return (0);
	str[s1_len] = '\0';
	ft_memcpy(str, s1, s1_len);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (len == 0 || start > s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	ft_memcpy(str, s + start, len);
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*s1_;
	const unsigned char	*s2_;
	size_t				i;

	s1_ = (const unsigned char *)s1;
	s2_ = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_[i] == '\0')
			return (-s2_[i]);
		if (s2_[i] == '\0')
			return (s1_[i]);
		if (s1_[i] != s2_[i])
			return (s1_[i] - s2_[i]);
		i++;
	}
	return (0);
}

/*==================LIBFT_END===========================*/

/**
 * separateWords - 주어진 문자열을 단어로 분리합니다.
 * 
 * @param line 단어로 분리할 문자열
 * @return void
 * @todo separate_words 를 사용한 후에는 syntax.words, syntax.line 메모리를 해제해야 합니다.
 */
void	lexer(t_syntax *syntax)
{
	const char	*op[9] = {"&&", "||", "|", "(", ")", ">", "<", ">>", "<<"};
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

static size_t	count_word(const char *line, const char **op)
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

static size_t	get_op(const char *s1, const char **op)
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

static size_t	get_word(const char *line, const char **op)
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

static size_t	close_quote(const char *line, const char quote)
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

static char	*extract_word(char *line, size_t *start, const char **op)
{
	size_t	i;
	char	*word;

	i = *start;
	word = NULL;
	i += get_word(line + i, op);
	if (line[i] == ' ')
		i++;
	word = ft_substr(line, *start, i - *start);
	*start = i;
	return (word);
}

static char	*extract_token(char *line, size_t *start, const char **op)
{
	char	*token;
	size_t	i;
	size_t	op_size;

	i = *start;
	op_size = get_op(line + i, op);
	token = ft_substr(line, *start, op_size);
	*start += op_size;
	return (token);
}
