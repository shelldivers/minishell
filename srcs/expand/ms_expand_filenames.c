/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filenames.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/02 17:13:10 by jeongwpa         ###   ########.fr       */
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
		ms_mark_asterisk(*argv);
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

void	ms_mark_asterisk(char *str)
{
	t_bool	quote;
	t_bool	dquote;

	quote = FALSE;
	dquote = FALSE;
	while (*str)
	{
		if (!quote && *str == '\"')
		{
			dquote = (t_bool) !dquote;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
			continue ;
		}
		else if (!dquote && *str == '\'')
		{
			quote = (t_bool) !quote;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
			continue ;
		}
		else if (!quote && !dquote && *str == '*')
			*str = ASTERISK;
		str++;
	}
}

static void	*quit(char **expanded, t_queue *result)
{
	int	i;

	if (expanded)
	{
		i = 0;
		while (expanded[i])
			free(expanded[i++]);
	}
	ms_destroy_queue(result, free);
	return (NULL);
}
