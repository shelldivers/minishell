#include "ft_printf.h"
#include "libft.h"
#include "ms_env.h"
#include "ms_expand.h"

static size_t	ft_strcspn(const char *str, const char *charset);

static char	*get_pos(char *str)
{
	t_bool	quote;

	quote = FALSE;
	while (*str)
	{
		if (!quote && *str == '\'')
			quote = TRUE;
		else if (quote && *str == '\'')
			quote = FALSE;
		else if (!quote && *str == '$')
			return (str);
		str++;
	}
	return (NULL);
}

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
		ms_dequote(*argv, '\'');
		argv++;
	}
	return (TRUE);
}

char	*ms_status_expansion(char *str, char *pos, int status)
{
	char	*nbr;
	char	*tmp;
	char	*tmp2;
	char	*replace;

	nbr = ft_sprintf("%d", status);
	if (!nbr)
		return (NULL);
	tmp = ft_strndup(str, pos - str);
	if (!tmp)
	{
		free(nbr);
		return (NULL);
	}
	tmp2 = ft_strjoin(tmp, nbr);
	free(tmp);
	free(nbr);
	if (!tmp2)
		return (NULL);
	replace = ft_strjoin(tmp2, pos + 2);
	free(tmp2);
	if (!replace)
		return (NULL);
	return (replace);
}

char	*ms_param_expansion(char *str, char *pos, t_env *env)
{
	char	*key;
	char	*val;
	char	*tmp;
	char	*tmp2;
	char	*replace;

	key = ft_strndup(pos + 1, ft_strcspn(pos + 1, " \t\n\"'\\$"));
	if (!key)
		return (NULL);
	val = ms_getenv(env, key);
	free(key);
	if (!val)
		val = "";
	tmp = ft_strndup(str, pos - str);
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(tmp, val);
	free(tmp);
	if (!tmp2)
		return (NULL);
	replace = ft_strjoin(tmp2, pos + ft_strcspn(pos + 1, " \t\n\"'\\$") + 1);
	free(tmp2);
	if (!replace)
		return (NULL);
	return (replace);
}

static size_t	ft_strcspn(const char *str, const char *charset)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (charset[j])
		{
			if (str[i] == charset[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}