#include "libft.h"
#include "ms_expand.h"
#include <dirent.h>
#include <stdlib.h>

/**
 * @errno ENOMEM
 */
char	*ms_wildcard_get_path(char *str)
{
	char	*path_end;
	int		i;

	i = 0;
	while (str[i] && str[i] != '*')
	{
		if (str[i] == '/')
			path_end = str + i;
		i++;
	}
	if (i == 0)
		return (ft_strdup("."));
	return (ft_strndup(str, path_end - str + 1));
}

/**
 * @errno ENOMEM
 */
char	*ms_wildcard_get_prefix(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '*')
	{
		if (str[i] == '/')
		{
			str = str + i + 1;
			i = 0;
		}
		else
			i++;
	}
	if (i == 0)
		return (ft_strdup(""));
	return (ft_strndup(str, i));
}

/**
 * @errno ENOMEM
 */
char	*ms_wildcard_get_suffix(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (ft_strdup(""));
	return (ft_strdup(str + i + 1));
}

/**
 * @errno ENOMEM
 */
char	*ms_wildcard_combine(char *d_name, char *path, char *suffix)
{
	char	*name;
	char	*tmp;

	tmp = ft_strjoin(d_name, suffix);
	if (!tmp)
		return (NULL);
	if (ft_strcmp(path, ".") == 0 || ft_strcmp(path, "..") == 0)
		return (tmp);
	name = ft_strjoin(path, tmp);
	free(tmp);
	return (name);
}
