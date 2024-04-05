/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:33:24 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 21:21:33 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_exec.h"
#include "ms_error.h"
#include "ms_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

static t_bool	ms_find_close_quote(char *word, int idx);

int	main(void)
{
	while (1)
	{
		char	*line;
		char	*new_line;

		line = readline("input: ");
		if (!line)
			break ;
		printf ("input: %s\n", line);
		new_line = ms_quote_removal_dup(line, 0, 0);
		printf("output: %s\n", new_line);
		free(line);
		free(new_line);
	}
}

char	*ms_quote_removal_dup(char *word, size_t i, size_t j)
{
	char	quote;
	char	*new_word;

	new_word = (char *)malloc(sizeof(char) * (ft_strlen(word) + 1));
	if (!new_word)
		return (NULL);
	while (word[i])
	{
		if ((word[i] == '\'' || word[i] == '\"')
			&& ms_find_close_quote(word, i))
		{
			quote = word[i];
			i++;
			while (word[i] && word[i] != quote)
				new_word[j++] = word[i++];
			i++;
		}
		else
			new_word[j++] = word[i++];
	}
	new_word[j] = '\0';
	return (new_word);
}

static t_bool	ms_find_close_quote(char *word, int idx)
{
	char	quote;
	size_t	i;

	i = idx;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
		{
			quote = word[i];
			i++;
			while (word[i] && word[i] != quote)
				i++;
			if (!word[i])
				return (FALSE);
			return (TRUE);
		}
	}
	return (FALSE);
}
