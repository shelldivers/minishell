/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:12:52 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 19:50:45 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ms_env.h"
#include "ms_expand.h"
#include "ms_parser.h"
#include "ms_exec.h"

static char		*check_env_val(char *val);

char	**ms_expand_params(char **argv, t_env *env)
{
	t_queue	*queue;
	char	**expanded;
	char	*tmp;

	queue = ms_init_queue();
	if (!queue)
		return (NULL);
	while (*argv)
	{
		tmp = check_env_val(*argv);
		if (!tmp)
			return (NULL);
		if (!ms_expand_param(queue, tmp, env))
		{
			ms_destroy_queue(queue, free);
			return (NULL);
		}
		argv++;
	}
	expanded = ms_queue_to_array(queue);
	ms_destroy_queue(queue, free);
	if (!expanded)
		return (NULL);
	return (expanded);
}

static char	*check_env_val(char *val)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strcmp(val, "\"$\"") == 0)
		tmp = ms_quote_removal_dup(val, 0, 0);
	else
		tmp = ft_strdup(val);
	return (tmp);
}
