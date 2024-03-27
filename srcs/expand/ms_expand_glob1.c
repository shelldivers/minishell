#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"
#include <dirent.h>

static char	*get_path_from_root(char *str);
static char	*get_path_from_cur(char *str);

// @TODO 여기서 quote 제거
t_bool	ms_get_path(t_glob *glob, char *str)
{
	char	*tmp;

	if (*str == '/')
		tmp = get_path_from_root(str);
	else
		tmp = get_path_from_cur(str);
	if (!tmp)
		return (FALSE);
	glob->path = tmp;
	return (TRUE);
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
		path = ft_strdup("");
		if (!path)
			return (NULL);
	}
	else
	{
		path = ft_strndup(str, pattern - str);
		if (!path)
			return (NULL);
	}
	return (path);
}
