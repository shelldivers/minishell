/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:50:39 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/04 16:14:08 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	clear_syntax(t_syntax *syntax)
{
	int	i;

	i = 0;
	if (syntax->line)
		free(syntax->line);
	if (syntax->words)
	{
		while (syntax->words[i])
		{
			free(syntax->words[i++]);
			syntax->words[i] = NULL;
		}
	}
	syntax->words_cnt = 0;
}

void	clear_token(t_token **token)
{
	int	i;

	i = 0;
	if (token)
	{
		while (token[i])
		{
			free(token[i]->value);
			free(token[i]);
			i++;
		}
		free(token);
	}
}

void	clear_parse(t_parse *parse)
{
	if (parse)
	{
		clear_parse(parse->left);
		clear_parse(parse->right);
		free(parse);
	}
}

void	clear_all(t_syntax *syntax, t_token **token, t_parse *parse)
{
	clear_syntax(syntax);
	clear_token(token);
	clear_parse(parse);
}
