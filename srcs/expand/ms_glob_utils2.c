#include "ms_expand.h"
#include "libft.h"

char	*get_pat(char *str, int is_root) // TODO : Failed to parse pattern
{
	int		i;
	char	*pattern;
	t_bool	quote;

	quote = FALSE;
	pattern = NULL;
	i = is_root;
	while (str[i])
	{
		if (!quote && str[i] == '\"')
			quote = TRUE;
		else if (quote && str[i] == '\"')
			quote = FALSE;
		else if (str[i] == '/')
			pattern = str + i + 1;
		else if (!quote && str[i] == '*')
			break ;
		i++;
	}
	if (is_root > 0 && !pattern)
		pattern = str + is_root;
	return (pattern);
}

char	*get_glob_pos(char *str)
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

char	*get_glob_start(const char *str, char *glob_pos)
{
	char	*glob_start;

	glob_start = glob_pos;
	while (glob_start != str && *glob_start != '/')
		glob_start--;
	if (*glob_start == '/')
		glob_start++;
	return (glob_start);
}

char	*get_glob_end(char *glob_pos)
{
	char	*glob_end;

	glob_end = glob_pos;
	while (*glob_end && *glob_end != '/')
		glob_end++;
	return (glob_end);
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
	pos = get_glob_pos(glob->pattern);
	glob->prefix = ft_strndup(glob->pattern, pos - glob->pattern);
	if (!glob->prefix)
		return (FALSE);
	glob->suffix = ft_strdup(pos + 1);
	if (!glob->suffix)
		return (FALSE);
	ms_remove_dquote(glob->prefix);
	ms_remove_dquote(glob->suffix);
	return (TRUE);
}
