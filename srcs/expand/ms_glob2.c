#include "ms_expand.h"
#include "libft.h"

static char	*get_pos(char *str);

t_bool	ms_get_pattern(t_glob *glob, char *str)
{
	char	*pos;
	char	*start;
	char	*end;

	pos = get_pos(str);
	if (!pos)
	{
		glob->pattern = ft_strdup("");
		return (TRUE);
	}
	start = pos;
	while (start != str && *start != '/')
		start--;
	if (*start == '/')
		start++;
	end = pos;
	while (*end && *end != '/')
		end++;
	glob->pattern = ft_strndup(start, end - start);
	if (!glob->pattern)
		return (FALSE);
	return (TRUE);
}

t_bool	ms_get_remain(t_glob *glob, char *str)
{
	char	*pos;
	char	*remain;

	pos = get_pos(str);
	if (!pos)
	{
		glob->remain = ft_strdup("");
		return (TRUE);
	}
	remain = ft_strchr(pos, '/');
	if (!remain)
		remain = ft_strdup("");
	else
		remain = ft_strdup(remain);
	if (!remain)
		return (FALSE);
	glob->remain = remain;
	return (TRUE);
}

t_bool	ms_parse_pattern(t_glob *glob)
{
	char	*pos;

	if (!glob->pattern)
		return (FALSE);
	if (*(glob->pattern) == '\0')
	{
		glob->prefix = ft_strdup("");
		glob->suffix = ft_strdup("");
		return (TRUE);
	}
	pos = get_pos(glob->pattern);
	glob->prefix = ft_strndup(glob->pattern, pos - glob->pattern);
	if (!glob->prefix)
		return (FALSE);
	glob->suffix = ft_strdup(pos + 1);
	if (!glob->suffix)
		return (FALSE);
	ms_dequote(glob->prefix, '\"');
	ms_dequote(glob->suffix, '\"');
	return (TRUE);
}

static char	*get_pos(char *str)
{
	t_bool	quote;

	quote = FALSE;
	while (*str)
	{
		if (!quote && *str == '\"')
			quote = TRUE;
		else if (quote && *str == '\"')
			quote = FALSE;
		else if (!quote && *str == '*')
			return (str);
		str++;
	}
	return (NULL);
}
