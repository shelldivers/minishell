#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"
#include <dirent.h>

static char	*get_path_from_root(char *str);
static char	*get_path_from_cur(char *str);

char	*ms_get_path(char *str)
{
	if (*str == '/')
		return (get_path_from_root(str));
	else
		return (get_path_from_cur(str));
}

char	*ms_get_pattern(char *str)
{
	size_t	i;
	char	*tmp;

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
		return (ft_strdup(str));
	return (ft_strndup(str, tmp - str));
}

static char	*get_path_from_root(char *str)
{
	int		i;
	char	*pattern;
	char	*path;

	i = 1;
	pattern = NULL;
	while (str[i] != '*')
	{
		if (str[i] == '/')
			pattern = str + i + 1;
		i++;
	}
	if (!pattern)
	{
		path = ft_strdup("/");
		if (!path)
			return (NULL);
	}
	else
	{
		path = ft_strndup(str, pattern - str - 1);
		if (!path)
			return (NULL);
	}
	return (path);
}

static char	*get_path_from_cur(char *str)
{
	int		i;
	char	*pattern;
	char	*path;

	i = 0;
	pattern = NULL;
	while (str[i] != '*')
	{
		if (str[i] == '/')
			pattern = str + i + 1;
		i++;
	}
	if (!pattern)
	{
		path = ft_strdup(".");
		if (!path)
			return (NULL);
	}
	else
	{
		path = ft_strndup(str, pattern - str - 1);
		if (!path)
			return (NULL);
	}
	return (path);
}
