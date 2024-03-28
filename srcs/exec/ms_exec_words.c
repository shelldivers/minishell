/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:21:46 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/28 18:08:16 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

size_t	ms_words_size(char **words)
{
	size_t	size;

	size = 0;
	if (!words)
		return (size);
	while (words[size])
		size++;
	return (size);
}

void	ms_clear_sec_dimentional(char **words)
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

t_bool	ms_create_words(t_exec *exec_info, char *word)
{
	char	**words;

	if (exec_info->words)
		free(exec_info->words);
	words = (char **)malloc(sizeof(char *) * 2);
	if (!words)
		return (FALSE);
	words[0] = word;
	words[1] = NULL;
	exec_info->words = words;
	exec_info->words_size = 1;
	return (TRUE);
}

t_bool	ms_add_word(t_exec *exec_info, char *word)
{
	char		**new_words;
	size_t		size;
	size_t		i;

	size = exec_info->words_size;
	new_words = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_words)
		return (FALSE);
	new_words[size + 1] = NULL;
	new_words[0] = exec_info->words[0];
	new_words[1] = word;
	i = 2;
	while (i <= size)
	{
		new_words[i] = exec_info->words[i - 1];
		i++;
	}
	free(exec_info->words);
	exec_info->words = new_words;
	exec_info->words_size++;
	return (TRUE);
}
