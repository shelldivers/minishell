/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_collect_words.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:21:46 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/26 18:13:03 by jiwojung         ###   ########.fr       */
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

void	ms_create_words(t_exec *exec_info, char *word)
{
	char	**words;

	if (exec_info->words)
		ms_clear_sec_dimentional(exec_info->words);
	words = (char **)malloc(sizeof(char *) * 2);
	if (!words)
		return (NULL);
	words[0] = ft_strdup(word);
	words[1] = NULL;
	exec_info->words = words;
}

char	**ms_add_word(t_exec *exec_info, char *word)
{
	const char		**old_words = exec_info->words;
	char			**new_words;
	size_t			size;

	size = exec_info->words_size;
	new_words = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_words)
		return (NULL);
	new_words[size + 1] = NULL;
	new_words[size] = ft_strdup(word);
	while (size--)
		new_words[size] = ft_strdup(old_words[size]);
	if (old_words)
		ms_clear_sec_dimentional(old_words);
	exec_info->words = new_words;
	exec_info->words_size++;
}
