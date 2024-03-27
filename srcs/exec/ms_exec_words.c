/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:21:46 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/27 20:15:33 by jiwojung         ###   ########.fr       */
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
		ms_clear_sec_dimentional(exec_info->words);
	words = (char **)malloc(sizeof(char *) * 2);
	if (!words)
		return (FALSE);
	words[0] = ft_strdup(word);
	if (!words[0])
	{
		free(words);
		return (FALSE);
	}
	words[1] = NULL;
	exec_info->words = words;
	exec_info->words_size = 1;
	return (TRUE);
}

t_bool	ms_add_word(t_exec *exec_info, char *word)
{
	char		**new_words;
	size_t		size;

	size = exec_info->words_size;
	new_words = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_words)
		return (FALSE);
	new_words[size + 1] = NULL;
	new_words[size] = ft_strdup(word);
	while (size--)
	{
		new_words[size] = ft_strdup(exec_info->words[size]);
		if (!new_words[size])
		{
			ms_clear_sec_dimentional(new_words);
			return (FALSE);
		}
	}
	if (exec_info->words)
		ms_clear_sec_dimentional(exec_info->words);
	exec_info->words = new_words;
	exec_info->words_size++;
	return (TRUE);
}
