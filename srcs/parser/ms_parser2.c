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

#include "ms_parser.h"
#include "libft.h"
#include "ms_error.h"
#include <stdio.h>
#include <stdlib.h>

static t_bool	assign_token(t_token *const *src, t_token **dst, int i);

/**
 * @errno ENOMEM 메모리 할당에 실패했을 경우 -> -1 반환
 */
int	ms_add_ast(t_ast *ast, t_token **token, int size, t_drill drill)
{
	int		curtok;
	t_ast	*new;

	if (!size)
		size = ms_get_token_size(token);
	if (!size)
		return (0);
	new = ms_new_ast(token, size);
	if (!new)
		return (ERROR);
	curtok = drill.f(new, new->token);
	if (drill.lr == LEFT)
	{
		if (ast->left)
			new->left = ast->left;
		ast->left = new;
	}
	else if (drill.lr == RIGHT)
	{
		while (ast->right)
			ast = ast->right;
		ast->right = new;
	}
	return (curtok);
}

/**
 * @errno ENOMEM 메모리 할당에 실패했을 경우
 */
t_ast	*ms_new_ast(t_token **token, int size)
{
	t_ast	*new_ast;

	if (!size || !token)
		return (NULL);
	new_ast = (t_ast *)malloc(sizeof(t_ast));
	if (!new_ast)
		return (NULL);
	ft_memset(new_ast, 0, sizeof(t_ast));
	new_ast->token = ms_tokenndup(token, size);
	if (!new_ast->token)
	{
		free(new_ast);
		return (NULL);
	}
	new_ast->token_size = size;
	new_ast->op = OPNONE;
	return (new_ast);
}

t_token	**ms_tokenndup(t_token **src, int size)
{
	t_token	**dst;
	int		i;

	dst = (t_token **)malloc(sizeof(t_token *) * (size + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dst[i] = (t_token *)malloc(sizeof(t_token));
		if (!dst[i] || !assign_token(src, dst, i))
		{
			ms_clear_token(dst);
			return (NULL);
		}
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

static t_bool	assign_token(t_token *const *src, t_token **dst, int i)
{
	dst[i]->type = src[i]->type;
	dst[i]->value = ft_strdup(src[i]->value);
	if (!dst[i]->value)
		return (FALSE);
	return (TRUE);
}

int	ms_get_token_size(t_token **token)
{
	int	size;

	size = 0;
	while (token[size])
		size++;
	return (size);
}
