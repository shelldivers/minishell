/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:29:36 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/08 19:23:57 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

static void		count_word(char *line, size_t *words_cnt, const char **sep);
static size_t	sepcmp(const char *s1, const char **s2);
static char		*extract_word(char *line, size_t *start, const char **sep);
static char		*extract_token(char *line, size_t *start, const char **sep);

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
	const char	*sep[9] = {"&&", "||", "|", "(", ")", ">", "<", ">>", "<<"};
	size_t		i;
	size_t		start;

	count_word(syntax->line, &syntax->words_cnt, sep);
	syntax->words = (char **)malloc(sizeof(char *) * (syntax->words_cnt + 1));
	if (!syntax->words)
		exit(EXIT_FAILURE);
	syntax->words[syntax->words_cnt] = NULL;
	i = 0;
	start = 0;
	while (i < syntax->words_cnt)
	{
		if (sepcmp(syntax->line + start, sep))
			syntax->words[i] = extract_token(syntax->line, &start, sep);
		else
			syntax->words[i] = extract_word(syntax->line, &start, sep);
		i++;
	}
	i = 0;
}

static size_t	sepcmp(const char *s1, const char **s2)
{
	size_t	i;

	i = 0;
	while (i < 9)
	{
		if (ft_strncmp(s1, s2[i], ft_strlen(s2[i])) == 0)
			return (ft_strlen(s2[i]));
		i++;
	}
	return (0);
}

static void	count_word(char *line, size_t *words_cnt, const char **sep)
{
	size_t	i;
	size_t	flag;

	i = 0;
	while (line[i])
	{
		if (sepcmp(line + i, sep))
		{
			if (flag)
				(*words_cnt)++;
			(*words_cnt)++;
			i += sepcmp(line + i, sep);
			flag = 0;
		}
		else
		{
			flag = 1;
			i++;
		}
	}
	if (flag)
		(*words_cnt)++;
}

static char	*extract_word(char *line, size_t *start, const char **sep)
{
	size_t	i;
	char	*word;

	i = *start;
	word = NULL;
	while (sepcmp(line + i, sep) == 0 && line[i])
		i++;
	word = ft_substr(line, *start, i - *start);
	*start = i;
	return (word);
}

static char	*extract_token(char *line, size_t *start, const char **sep)
{
	char	*token;
	size_t	i;
	size_t	sep_size;

	i = *start;
	sep_size = sepcmp(line + i, sep);
	token = ft_substr(line, *start, sep_size);
	*start += sep_size;
	return (token);
}
