/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:29:36 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 20:58:10 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_parser.h"

char	*ms_extract_word(char *line, int *start, const char **op)
{
	int		i;
	char	*word;

	i = *start;
	i += ms_get_word(line + i, op);
	word = ft_substr(line, *start, i - *start);
	*start = i;
	return (word);
}

char	*ms_extract_token(char *line, int *start, const char **op)
{
	char	*token;
	int		i;
	int		op_len;

	i = *start;
	op_len = ms_get_op(line + i, op);
	token = ft_substr(line, *start, op_len);
	*start += op_len;
	return (token);
}

int	ms_get_op(const char *s1, const char **op)
{
	int	i;
	int	op_len;

	i = 0;
	while (i < OP_SIZE)
	{
		op_len = (int) ft_strlen(op[i]);
		if (ft_strncmp(s1, op[i], op_len) == 0)
			return (op_len);
		i++;
	}
	return (0);
}

int	ms_get_word(const char *line, const char **op)
{
	int	i;

	i = 0;
	while (line[i] != ' ' && line[i] != '\0' \
	&& ms_get_op(line + i, op) == 0)
	{
		if (line[i] == '\'' || line[i] == '"')
			i += ms_close_quote(line + i, line[i]);
		else
			i++;
	}
	return (i);
}

int	ms_close_quote(const char *line, char quote)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == quote)
			return (i + 1);
		i++;
	}
	return (1);
}
