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

static char		*get_pos(const char *str);
static t_bool	is_cspn(char ch);
static void		remove_empty_str(char **argv);

/**
 * @details parameter expansion\n
 * - 환경 변수만 처리하고, 쉘 변수는 처리하지 않습니다.\n
 * - 중괄호(`{}`)는 처리하지 않습니다.\n
 * - `?`를 제외한 다른 특수 문자를 처리하지 않습니다.
 * @see https://runebook.dev/ko/docs/bash/special-parameters
 */
t_bool	ms_expand_param(char **argv, t_env *env, int status)
{
	char	*pos;
	char	*replace;

	while (*argv)
	{
		while (1)
		{
			pos = get_pos(*argv);
			if (!pos)
				break ;
			replace = ms_dollar_expand(*argv, pos, status, env);
			if (!replace)
				return (FALSE);
			free(*argv);
			*argv = replace;
		}
		if (**argv == '\0')
			remove_empty_str(argv);
		else
			argv++;
	}
	return (TRUE);
}

static void	remove_empty_str(char **argv)
{
	char	**dest;
	char	*tmp;

	tmp = *argv;
	dest = argv;
	while (*dest)
	{
		*dest = *(dest + 1);
		dest++;
	}
	free(tmp);
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
