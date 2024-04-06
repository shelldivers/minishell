/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:12:52 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/05 13:54:58 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ms_env.h"
#include "ms_expand.h"
#include "ms_parser.h"

static t_bool	re_syntaxing(t_queue *queue, const char *str);
static char		*get_pos(const char *str);
static t_bool	is_cspn(char ch);

/**
 * @details parameter expansion\n
 * - 환경 변수만 처리하고, 쉘 변수는 처리하지 않습니다.\n
 * - 중괄호(`{}`)는 처리하지 않습니다.\n
 * - `?`를 제외한 다른 특수 문자를 처리하지 않습니다.
 * @see https://runebook.dev/ko/docs/bash/special-parameters
 */
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
		tmp = ft_strdup(*argv);
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

t_bool	ms_expand_param(t_queue *queue, char *str, t_env *env)
{
	char	*pos;
	char	*replace;
	t_bool	result;

	while (1)
	{
		pos = get_pos(str);
		if (!pos)
			break ;
		replace = ms_dollar_expand(str, pos, env);
		free(str);
		if (!replace)
			return (FALSE);
		str = replace;
	}
	result = re_syntaxing(queue, str);
	free(str);
	if (!result)
		return (FALSE);
	return (TRUE);
}

static t_bool	re_syntaxing(t_queue *queue, const char *str)
{
	t_syntax	re_syntax;
	int			i;

	if (*str == '\0')
		return (TRUE);
	re_syntax = (t_syntax){(char *)str, NULL, 0};
	ms_tokenizer(&re_syntax);
	i = 0;
	while (re_syntax.words[i])
	{
		if (!ms_enqueue(queue, re_syntax.words[i]))
		{
			while (re_syntax.words[i])
				free(re_syntax.words[i++]);
			free(re_syntax.words);
			return (FALSE);
		}
		i++;
	}
	free(re_syntax.words);
	return (TRUE);
}

static char	*get_pos(const char *str)
{
	char	*pos;
	t_bool	dquote;
	t_bool	quote;

	pos = (char *) str;
	dquote = FALSE;
	quote = FALSE;
	while (*pos)
	{
		if (!quote && *pos == '\"')
			dquote = (t_bool) !dquote;
		else if (!dquote && *pos == '\'')
		{
			if (quote || ft_strchr(pos + 1, '\''))
				quote = (t_bool) !quote;
		}
		else if (!quote && *pos == '$' && *(pos + 1) != '\0'
			&& is_cspn(*(pos + 1)))
			return (pos);
		pos++;
	}
	return (NULL);
}

static t_bool	is_cspn(char ch)
{
	if (ft_isalnum(ch) || ch == '_' || ch == '?')
		return (TRUE);
	return (FALSE);
}
