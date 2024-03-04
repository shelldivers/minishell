/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:44:20 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/04 16:36:50 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	init_syntax(t_syntax *syntax)
{
	syntax->line = NULL;
	syntax->words = NULL;
	syntax->words_cnt = 0;
}

void	init_parse(t_parse *parse, t_token **token, size_t size)
{
	parse = (t_parse *)malloc(sizeof(t_parse));
	if (!parse)
		exit (1);
	parse->grammar = GAND_OR;
	parse->token = token;
	parse->token_size = size;
	parse->left = NULL;
	parse->right = NULL;
}
