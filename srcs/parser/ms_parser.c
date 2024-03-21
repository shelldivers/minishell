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
#include "ms_parser.h"
#include "../libft/includes/libft.h"

int	ms_parser(t_ast *ast, t_token **token, size_t size)
{
	size_t	cursor;

	ast = ms_new_ast(token, size);
	if (!ast)
		return (0);
	cursor = ms_add_ast(ast, token, ms_is_and_or, size, LEFT);
	if (cursor != size)
	{
		ms_clear_ast(ast);
		ms_clear_token(token);
		return (0);
	}
	ms_clear_ast(ast);
	ms_clear_token(token);
	return (1);
}

size_t	ms_add_ast(t_ast *ast, t_token **token, \
size_t(f)(t_ast *, t_token **), size_t size, enum e_lr lr)
{
	size_t	curtok;
	t_ast	*new;

	if (!size)
		size = ms_tokenlen(token);
	new = ms_new_ast(token, size);
	if (!new)
		return (0);
	curtok = (f(new, new->token));
	if (curtok && lr == LEFT)
	{
		if (ast->left)
			new->left = ast->left;
		ast->left = new;
	}
	else if (curtok && lr == RIGHT)
	{
		if (ast->right)
			new->right = ast->right;
		ast->right = new;
	}
	else
		ms_clear_ast(new);
	return (curtok);
}

t_ast	*ms_new_ast(t_token **token, size_t size)
{
	t_ast	*new_ast;

	if (!size || !token)
		return (NULL);
	new_ast = (t_ast *)malloc(sizeof(t_ast));
	if (!new_ast)
		return (NULL);
	new_ast->token = ms_tokenndup(token, size);
	if (!new_ast->token)
	{
		free(new_ast);
		return (NULL);
	}
	new_ast->token_size = size;
	new_ast->op = OPNONE;
	new_ast->left = NULL;
	new_ast->right = NULL;
	return (new_ast);
}

t_token	**ms_tokenndup(t_token **src, size_t size)
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
			ms_clear_token(dst);
			return (NULL);
		}
		dst[size]->type = src[size]->type;
		dst[size]->value = ft_strdup(src[size]->value);
		if (!dst[size]->value)
		{
			ms_clear_token(dst);
			return (NULL);
		}
	}
	return (dst);
}

size_t	ms_tokenlen(t_token **token)
{
	size_t	len;

	len = 0;
	while (token[len])
		len++;
	return (len);
}
