/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:21:46 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/03 16:24:46 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ms_exec.h"

t_bool	ms_add_word(t_exec *exec_info, char *word)
{
	char		**new_words;
	size_t		i;

	new_words = (char **)malloc(sizeof(char *) * (exec_info->words_size + 2));
	if (!new_words)
		return (FALSE);
	i = 0;
	new_words[exec_info->words_size] = word;
	new_words[exec_info->words_size + 1] = NULL;
	while (i < exec_info->words_size)
	{
		new_words[i] = exec_info->words[i];
		i++;
	}
	if (exec_info->words)
		free(exec_info->words);
	exec_info->words = new_words;
	exec_info->words_size++;
	return (TRUE);
}

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
