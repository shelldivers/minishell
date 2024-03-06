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
	int		prefix_end;

	i = 0;
	while (str[i] && str[i] != '*')
	{
		if (str[i] == '/')
			prefix_end = i;
		i++;
	}
	if (i == 0)
		return (ft_strdup(""));
	return (ft_strndup(str, prefix_end + 1));
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

char	*ms_wildcard_get_match(char *str)
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
char	*ms_wildcard_combine(char *d_name, char *prefix, char *suffix)
{
	char	*name;
	char	*tmp;

	tmp = ft_strjoin(prefix, d_name);
	if (!tmp)
		return (NULL);
	name = ft_strjoin(tmp, suffix);
	free(tmp);
	return (name);
}

t_bool	ms_wildcard_is_match(char *name, int type, char *match, char *suffix)
{
	t_bool	is_dir;

	if (ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0)
		return (FALSE);
	is_dir = FALSE;
	if (ft_strchr(suffix, '/') != NULL)
		is_dir = TRUE;
	if (is_dir && type != DT_DIR)
		return (FALSE);
	if (ft_strncmp(name, match, ft_strlen(match)) != 0){
		return (FALSE);}
	return (TRUE);
}
