/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_collect_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:21:46 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/21 16:58:13 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

void	ms_clear_words(char **words)
{
	int	i;

	i = 0;
	if (!words)
		return ;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

char	**ms_create_words(char *word)
{
	char	**words;

	words = (char **)malloc(sizeof(char *) * 2);
	if (!words)
		return (NULL);
	words[0] = ft_strdup(word);
	words[1] = NULL;
	return (words);
}

char	**ms_add_word(char **words, size_t size, char *word)
{
	char	**new_words;
	int		i;

	new_words = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_words)
		return (NULL);
	i = 0;
	if (words)
	{
		while (i < size)
		{
			new_words[i] = ft_strdup(words[i]);
			i++;
		}
		ms_clear_words(words);
	}
	new_words[i] = ft_strdup(word);
	new_words[i + 1] = NULL;
	return (new_words);
}
