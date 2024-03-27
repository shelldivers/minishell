#include "ms_expand.h"
#include "libft.h"

t_bool	ms_get_pattern(t_glob *glob, char *str)
{
	size_t	i;
	char	*tmp;
	char	*pattern;

	i = 0;
	while (str[i] != '*')
	{
		if (str[i] != '/')
			i++;
		else
		{
			str = str + i + 1;
			i = 0;
		}
	}
	tmp = ft_strchr(str, '/');
	if (!tmp || *(tmp + 1) == '\0')
		pattern = ft_strdup(str);
	else
		pattern = ft_strndup(str, tmp - str);
	if (!pattern)
		return (FALSE);
	glob->pattern = pattern;
	return (TRUE);
}

t_bool	ms_get_remain(t_glob *glob, char *str)
{
	char	*remain;

	while (*str != '*')
		str++;
	remain = ft_strchr(str, '/');
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
	char	*pattern;

	if (!glob->pattern)
		return (FALSE);
	pattern = glob->pattern;
	while (*pattern != '*')
		pattern++;
	glob->prefix = ft_strndup(glob->pattern, pattern - glob->pattern);
	if (!glob->prefix)
		return (FALSE);
	glob->suffix = ft_strdup(pattern + 1);
	if (!glob->suffix)
		return (FALSE);
	return (TRUE);
}
