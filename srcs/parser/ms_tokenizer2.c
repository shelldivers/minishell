/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:29:36 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 18:13:00 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "../libft/includes/libft.h"

char	*ms_extract_word(\
char *line, size_t *start, const char **op, size_t op_size)
{
	size_t	i;
	char	*word;

	i = *start;
	word = NULL;
	i += ms_get_word(line + i, op, op_size);
	word = ft_substr(line, *start, i - *start);
	*start = i;
	return (word);
}

char	*ms_extract_token(\
char *line, size_t *start, const char **op, size_t op_size)
{
	char	*token;
	size_t	i;
	size_t	op_len;

	i = *start;
	op_len = ms_get_op(line + i, op, op_size);
	token = ft_substr(line, *start, op_len);
	*start += op_len;
	return (token);
}

size_t	ms_get_op(const char *s1, const char **op, size_t op_size)
{
	size_t	i;
	size_t	op_len;

	i = 0;
	while (i < op_size)
	{
		op_len = ft_strlen(op[i]);
		if (ft_strncmp(s1, op[i], op_len) == 0)
			return (op_len);
		i++;
	}
	return (0);
}

size_t	ms_get_word(const char *line, const char **op, size_t op_size)
{
	size_t	i;

	i = 0;
	while (line[i] != ' ' && line[i] != '\0' \
	&& ms_get_op(line + i, op, op_size) == 0)
	{
		if (line[i] == '\'' || line[i] == '"')
			i += ms_close_quote(line + i, line[i]);
		else
			i++;
	}
	return (i);
}

size_t	ms_close_quote(const char *line, const char quote)
{
	size_t	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == quote)
			return (i + 1);
		i++;
	}
	return (1);
}
