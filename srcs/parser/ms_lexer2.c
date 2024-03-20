/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:29:36 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 16:04:39 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "../libft/includes/libft.h"

char	*ms_extract_word(char *line, size_t *start, const char **op)
{
	size_t	i;
	char	*word;

	i = *start;
	word = NULL;
	i += ms_get_word(line + i, op);
	word = ft_substr(line, *start, i - *start);
	*start = i;
	return (word);
}

char	*ms_extract_token(char *line, size_t *start, const char **op)
{
	char	*token;
	size_t	i;
	size_t	op_size;

	i = *start;
	op_size = ms_get_op(line + i, op);
	token = ft_substr(line, *start, op_size);
	*start += op_size;
	return (token);
}
