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
#include "ms_parser.h"
#include "libft.h"
#include "ms_error.h"

static int	ms_tokenlen(t_token **token);

void	ms_parser(t_ast **ast, t_token **token, int size)
{
	int	curtok;

	*ast = ms_new_ast(token, size);
	if (!*ast)
	{
		ms_puterror_cmd(NULL, "malloc");
		return ;
	}
	curtok = ms_add_ast(*ast, token, ms_is_and_or, size, LEFT);
	if (curtok == -1)
	{
		ms_puterror_cmd(NULL, "malloc");
		ms_clear_ast(ast);
		return ;
	}
	else if (curtok != size)
	{
		ms_parser_error_handler(token, curtok);
		ms_clear_ast(ast);
	}
}

/**
 * @errno ENOMEM 메모리 할당에 실패했을 경우 -> -1 반환
 */
int	ms_add_ast(t_ast *ast, t_token **token, \
int (f)(t_ast *, t_token **), int size, enum e_lr lr)
{
	int		curtok;
	t_ast	*new;

	if (!size)
		size = ms_tokenlen(token);
	new = ms_new_ast(token, size);
	if (!new)
		return (ERROR);
	curtok = (f(new, new->token));
	if (lr == LEFT)
	{
		if (ast->left)
			new->left = ast->left;
		ast->left = new;
	}
	else if (lr == RIGHT)
	{
		while (ast->right)
			ast = ast->right;
		ast->right = new;
	}
	else
		ms_clear_ast(&new);
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
		if (!dst[i])
		{
			ms_clear_token(dst);
			return (NULL);
		}
		dst[i]->type = src[i]->type;
		dst[i]->value = ft_strdup(src[i]->value);
		if (!dst[i]->value)
		{
			ms_clear_token(dst);
			return (NULL);
		}
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

static int	ms_tokenlen(t_token **token)
{
	int	len;

	len = 0;
	while (token[len])
		len++;
	return (len);
}
