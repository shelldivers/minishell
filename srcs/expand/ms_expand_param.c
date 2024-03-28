#include "ft_printf.h"
#include "ms_env.h"
#include "ms_expand.h"

static char		*get_pos(char *str);

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
		while (TRUE)
		{
			pos = get_pos(*argv);
			if (!pos)
				break ;
			if (pos[1] == '?')
				replace = ms_status_expansion(*argv, pos, status);
			else
				replace = ms_param_expansion(*argv, pos, env);
			if (!replace)
				return (FALSE);
			free(*argv);
			*argv = replace;
		}
		ms_remove_quote(*argv);
		argv++;
	}
	return (TRUE);
}

static char	*get_pos(char *str)
{
	t_bool	dquote;
	t_bool	quote;

	dquote = FALSE;
	quote = FALSE;
	while (*str)
	{
		if (!quote && !dquote && *str == '\"')
			dquote = TRUE;
		else if (!quote && dquote && *str == '\"')
			dquote = FALSE;
		else if (!dquote && !quote && *str == '\'')
			quote = TRUE;
		else if (!dquote && quote && *str == '\'')
			quote = FALSE;
		else if (!quote && *str == '$')
			return (str);
		str++;
	}
	return (NULL);
}
