/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filenames.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/03 13:03:01 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"

static void	*quit(char **expanded, t_queue *result);

char	**ms_expand_filenames(char **argv)
{
	t_queue	*result;
	char	**expanded;

	result = ms_init_queue();
	if (!result)
		return (NULL);
	while (*argv)
	{
		expanded = ms_expand_filename(*argv);
		if (!expanded)
			return (quit(NULL, result));
		if (!ms_enqueue_array(result, expanded))
			return (quit(expanded, result));
		free(expanded);
		argv++;
	}
	expanded = ms_queue_to_array(result);
	ms_destroy_queue(result, free);
	return (expanded);
}

static void	*quit(char **expanded, t_queue *result)
{
	int	i;

	if (expanded)
	{
		i = 0;
		while (expanded[i])
			free(expanded[i++]);
		free(expanded);
	}
	ms_destroy_queue(result, free);
	return (NULL);
}
