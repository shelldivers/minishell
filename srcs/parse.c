/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:24:28 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/11 19:12:42 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

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

size_t	add_ast(t_ast *ast, t_token **token, \
size_t(f)(t_ast *, t_token **), size_t size, enum e_lr lr)
{
	size_t	cursor;
	t_ast	*new;

	if (!size)
		size = tokenlen(token);
	new = new_ast(token, size);
	if (!new)
		return (0);
	cursor = 0;
	cursor += (f(new, new->token));
	if (cursor && lr == LEFT)
	{
		if (ast->left)
			new->left = ast->left;
		ast->left = new;
	}
	else if (cursor && lr == RIGHT)
	{
		if (ast->right)
			new->right = ast->right;
		ast->right = new;
	}
	else
		clear_ast(new);
	return (cursor);
}

t_ast	*new_ast(t_token **token, size_t size)
{
	t_ast	*new_ast;

	if (!size || !token)
		return (NULL);
	new_ast = (t_ast *)malloc(sizeof(t_ast));
	if (!new_ast)
		return (NULL);
	new_ast->token = tokenndup(token, size);
	if (!new_ast->token)
	{
		free(new_ast);
		return (NULL);
	}
	new_ast->token_size = size;
	new_ast->grammar = GNONE;
	new_ast->op = OPNONE;
	new_ast->left = NULL;
	new_ast->right = NULL;
	return (new_ast);
}

t_token	**tokenndup(t_token **src, size_t size)
{
	t_token	**dst;

	dst = (t_token **)malloc(sizeof(t_token *) * (size + 1));
	if (!dst)
		return (NULL);
	dst[size] = NULL;
	while (size)
	{
		size--;
		dst[size] = (t_token *)malloc(sizeof(t_token));
		if (!dst[size])
		{
			clear_token(dst);
			return (NULL);
		}
		dst[size]->type = src[size]->type;
		dst[size]->value = ft_strdup(src[size]->value);
		if (!dst[size]->value)
		{
			clear_token(dst);
			return (NULL);
		}
	}
	return (dst);
}

size_t	tokenlen(t_token **token)
{
	size_t	len;

	len = 0;
	while (token[len])
		len++;
	return (len);
}
