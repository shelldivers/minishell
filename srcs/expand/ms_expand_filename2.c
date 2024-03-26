#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"
#include <dirent.h>

typedef struct s_wildcard
{
	char	*path;
	char	*prefix;
	char	*pattern;
	char	*suffix;
	char	*remainder;
}	t_wildcard;

char	*ms_get_prefix(char *pattern)
{
	size_t	i;

	i = 0;
	while (pattern[i] != '*')
	{
		if (pattern[i] != '/')
			i++;
		else
		{
			pattern = pattern + i + 1;
			i = 0;
		}
	}
	return pattern;
}

t_bool	ms_match_pattern(char *d_name, char *pattern)
{

}

/**
 * @todo : 매개변수 구조체로 합체
 */
t_bool	entry_loop(t_queue *queue, DIR *dir, char *path, char *pattern, char *remainder)
{
	struct dirent	*entry;
	char			*full_path;

	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (!ms_match_pattern(entry->d_name, pattern))
			continue ;
		full_path = ms_join_path(path, entry->d_name, remainder);	// todo
		if (!ms_enqueue(queue, entry->d_name))
			return (FALSE);
	}
	return (TRUE);
}

t_bool	ms_filename_expansion(t_queue *queue, char *str, t_env *env)
{
	char	*path;
	char	*pattern;
	char	*remainder;
	DIR		*dir;
	t_bool	result;

	path = ms_get_path(str);
	if (!path)
		return (FALSE);
	pattern = ms_get_pattern(str);
	if (!pattern)
	{
		free(path);
		return (FALSE);
	}
	remainder = ms_get_remainder(str);	// todo
	if (!remainder)
	{
		free(path);
		free(pattern);
		return (FALSE);
	}
	dir = opendir(str);
	if (!dir)
		return (FALSE);
	result = entry_loop(queue, dir, path, pattern, remainder);
	closedir(dir);
	free(path);
	free(pattern);
	return (result);
}
