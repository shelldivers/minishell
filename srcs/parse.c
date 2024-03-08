/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:24:28 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/08 11:38:52 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

size_t	add_parse(t_parse *parse, t_token **token, size_t token_size, \
size_t(f)(t_parse *, t_token **), enum e_lr lr)
{
	size_t	cursor;

	cursor = 0;
	if (lr == LEFT)
	{
		parse->left = ms_new_parse(token, OPNONE, token_size);
		parse->left->token_size = token_size;
		cursor = (f(parse->left, token));
		backtracking_free(&(parse->left));
	}
	else if (lr == RIGHT)
	{
		parse->right = ms_new_parse(token, OPNONE, token_size);
		parse->right->token_size = token_size;
		cursor = (f(parse->right, token));
		backtracking_free(&(parse->right));
	}
	return (cursor);
}

// void	isterminal(t_parse *parse, t_token **token)
// {
// 	const enum e_grammar	grammar[4] = {GWORD, GSUBSHELL, GIO_FILE, GIO_HERE};
// 	size_t	i;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		if (parse->grammar == grammar[i])
// 		{
// 			parse->left = ms_new_parse(token, OPNONE, 0);
// 			parse->left->token_size = 1;
// 			parse->left->grammar = parse->grammar;
// 			parse->left->op = OPNONE;
// 			parse->left->left = NULL;
// 			parse->left->right = NULL;
// 			break ;
// 		}
// 		i++;
// 	}
// }
