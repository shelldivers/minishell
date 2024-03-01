/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:29:36 by jiwojung          #+#    #+#             */
/*   Updated: 2024/02/29 15:54:11 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

static void	count_word(char *line, size_t *words_cnt);
static char	*extract_word(char *line, size_t *start);
static char	*extract_word2(char *line, size_t *start, size_t end);
static void	close_delimiter(char *line, size_t *start, char delimiter);

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
	size_t			i;
	size_t			start;

	count_word(syntax->line, &syntax->words_cnt);
	syntax->words = (char **)malloc(sizeof(char *) * (syntax->words_cnt + 1));
	if (!syntax->words)
		exit(EXIT_FAILURE);
	syntax->words[syntax->words_cnt] = NULL;
	i = 0;
	start = 0;
	while (i < syntax->words_cnt)
	{
		while (syntax->line[start] == ' ' && syntax->line[start] != '\0')
			start++;
		syntax->words[i] = extract_word(syntax->line, &start);
		i++;
	}
	i = 0;
}

static void	count_word(char *line, size_t *words_cnt)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"' || line[i] == '(')
			close_delimiter(line, &i, line[i]);
		if ((line[i] != ' ' && line[i] != '\0' && line[i] != '|') \
		&& (line[i + 1] == ' ' || line[i + 1] == '\0' || line[i + 1] == '|'))
			(*words_cnt)++;
		else if (line[i] == '|' || line[i] == ')')
			(*words_cnt)++;
		i++;
	}
}

static char	*extract_word(char *line, size_t *start)
{
	size_t	i;

	i = *start;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"' \
		|| line[i] == '(')
			close_delimiter(line, &i, line[i]);
		if ((line[i] != ' ' && line[i] != '\0' \
		&& line[i] != '|') \
		&& (line[i + 1] == ' ' || line[i + 1] == '\0' \
		|| line[i + 1] == '|'))
			return (extract_word2(line, start, i));
		else if (line[i] == '|' || line[i] == ')')
			return (extract_word2(line, start, i));
		i++;
	}
	return (NULL);
}

static char	*extract_word2(char *line, size_t *start, size_t end)
{
	char	*word;

	word = NULL;
	word = ft_substr(line, *start, end - *start + 1);
	*start = end + 1;
	return (word);
}

static void	close_delimiter(char *line, size_t *start, char delimiter)
{
	size_t	i;

	i = 1;
	if (delimiter == '(')
		delimiter = ')';
	while (line[*(start) + i])
	{
		if (line[*(start) + i] == delimiter)
		{
			*start += i;
			return ;
		}
		i++;
	}
}
