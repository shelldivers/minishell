/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:29:36 by jiwojung          #+#    #+#             */
/*   Updated: 2024/02/25 19:03:06 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

static char		*extract_word2(char *line, size_t *start, size_t i);
static char		*extract_word(\
char *line, size_t *start, size_t quote_cnt, size_t dquote_cnt);
static size_t	count_word(char *line, size_t quote_cnt, size_t dquote_cnt);	

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

void	separate_words(t_syntax *syntax)
{
	const size_t	words_cnt = count_word(syntax->line, 0, 0);
	size_t			i;
	size_t			start;

	syntax->word_list = (char **)malloc(sizeof(char *) * (words_cnt + 1));
	if (!syntax->word_list)
		exit(EXIT_FAILURE);
	i = 0;
	start = 0;
	// printf("words_cnt : %zu\n", words_cnt);
	while (i < words_cnt)
	{
		while (syntax->line[start] == ' ' && syntax->line[start] != '\0')
			start++;
		syntax->word_list[i] = extract_word(syntax->line, &start, 0, 0);
		i++;
	}
	// testcase
	// i = 0;
	// while (i < words_cnt)
	// {
	// 	printf("syntax->word_list[%zu] : %s\n", i, syntax->word_list[i]);
	// 	i++;
	// }
}

static size_t	count_word(char *line, size_t quote_cnt, size_t dquote_cnt)
{
	size_t			words_cnt;
	size_t			i;
	const size_t	len = ft_strlen(line);

	words_cnt = 0;
	i = 0;
	while (i < len)
	{
		if (line[i] == '"' && quote_cnt % 2 == 0)
			dquote_cnt++;
		else if (line[i] == '\'' && dquote_cnt % 2 == 0)
			quote_cnt++;
		if (line[i] != ' ' && (line[i + 1] == ' ' || line[i + 1] == '\0') \
		&& quote_cnt % 2 == 0 && dquote_cnt % 2 == 0)
			words_cnt++;
		else if (line[i] != ' ' && line[i + 1] == '\0' \
		&& (quote_cnt % 2 == 1 || dquote_cnt % 2 == 1))
			words_cnt++;
		i++;
	}
	return (words_cnt);
}

static char	*extract_word(\
char *line, size_t *start, size_t quote_cnt, size_t dquote_cnt)
{
	size_t	i;

	i = 0;
	while (line[*start + i])
	{
		if (line[*start + i] == '"' && quote_cnt % 2 == 0)
			dquote_cnt++;
		else if (line[*start + i] == '\'' && dquote_cnt % 2 == 0)
			quote_cnt++;
		if (line[*start + i] != ' ' \
		&& (line[*start + i + 1] == ' ' || line[*start + i + 1] == '\0') \
		&& quote_cnt % 2 == 0 && dquote_cnt % 2 == 0)
			return (extract_word2(line, start, i));
		else if (line[*start + i] != ' ' && line[*start + i + 1] == '\0' \
		&& (quote_cnt % 2 == 1 || dquote_cnt % 2 == 1))
			return (extract_word2(line, start, i));
		i++;
	}
	return (NULL);
}

static char	*extract_word2(char *line, size_t *start, size_t i)
{
	char	*word;

	word = ft_substr(line, *start, i + 1);
	*start += i + 1;
	return (word);
}
