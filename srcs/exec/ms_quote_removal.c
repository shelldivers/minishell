/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quote_removal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:33:24 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 13:33:59 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static t_bool	ms_find_close_quote(char *word, int idx);

char	*ms_quote_removal(char *word, size_t i, size_t j)
{
	char	quote;
	char	*new_word;

	new_word = (char *)malloc(sizeof(char) * (ft_strlen(word) + 1));
	if (!new_word)
		return (NULL);
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
		{
			quote = word[i];
			if (ms_find_close_quote(word, i) == TRUE)
			{
				i++;
				while (word[i] && word[i] != quote)
					new_word[j++] = word[i++];
				i++;
			}
		}
		else
			new_word[j++] = word[i++];
	}
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
			while (word[i] && word[i] != quote)
				i++;
			if (!word[i])
				return (FALSE);
			return (TRUE);
		}
	}
	return (FALSE);
}
