/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:49:24 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/19 19:51:56 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

/*==================LIBFT_START===========================*/

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isnumeric(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (s[cnt] != '\0')
		cnt++;
	return (cnt);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
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

static char	*ft_strdup(const char *s1)
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

static char	*ft_substr(char const *s, unsigned int start, size_t len)
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

static size_t	ft_strcmp(char *dst, const char *src)
{
	while (*dst && *src && *dst == *src)
	{
		dst++;
		src++;
	}
	if (*dst == *src)
		return (0);
	return (1);
}

/*==================LIBFT_END===========================*/

/*================tokenize.c_START================*/

//token  AND_IF    OR_IF    PIPE    LBRACE    RBRACE
/*      '&&'      '||'     '|'       '('       ')'    */


//token  DLESS  DGREAT   DREAD  DWRITE
/*      '<<'   '>>'     '<'     '>'    */

t_token			**tokenize(t_syntax *syntax);
static t_token	*new_token(char *value);
static void		set_tokentype(t_token **token);
static void		set_ionumber(t_token **token);

t_token	**tokenize(t_syntax *syntax)
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
		token[i] = new_token(syntax->words[i]);
		i++;
	}
	token[i] = NULL;
	set_ionumber(token);
	return (token);
}

static void	set_ionumber(t_token **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (ft_isdigit(token[i]->value[0]) && ft_strlen(token[i]->value) == 1 \
		&& token[i + 1] && (token[i + 1]->type == TDLESS \
		|| token[i + 1]->type == TDGREAT || token[i + 1]->type == TDREAD \
		|| token[i + 1]->type == TDWRITE))
			token[i]->type = TIO_NUMBER;
		i++;
	}
}

static t_token	*new_token(char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->value = ft_strdup(value);
	set_tokentype(&token);
	return (token);
}

static void	set_tokentype(t_token **token)
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

/*================tokenize.c_END================*/
