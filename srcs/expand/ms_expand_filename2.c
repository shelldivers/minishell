#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"
#include <dirent.h>
#include <errno.h>

char	*ms_join_path(char *entry, t_glob *glob)
{
	char	*full_path;
	size_t	path_len;
	size_t	entry_len;
	size_t	remain_len;

	path_len = ft_strlen(glob->path);
	entry_len = ft_strlen(entry);
	remain_len = ft_strlen(glob->remain);
	full_path = (char *)malloc(path_len + entry_len + remain_len + 1);
	if (!full_path)
		return (NULL);
	ft_memcpy(full_path, glob->path, path_len);
	ft_memcpy(full_path + path_len, entry, entry_len);
	ft_memcpy(full_path + path_len + entry_len, glob->remain, remain_len);
	full_path[path_len + entry_len + remain_len] = '\0';
	return (full_path);
}

t_bool	ms_match_pattern(struct dirent *entry, t_glob *glob)
{
	char	*d_name;
	size_t	prefix_len;
	size_t	suffix_len;

	d_name = entry->d_name;
	if (*(glob->remain) == '/' && entry->d_type != DT_DIR)
		return (FALSE);
	prefix_len = ft_strlen(glob->prefix);
	suffix_len = ft_strlen(glob->suffix);
	if (ft_strncmp(d_name, glob->prefix, prefix_len) != 0)
		return (FALSE);
	if (ft_strcmp(d_name + ft_strlen(d_name) - suffix_len, glob->suffix) != 0)
		return (FALSE);
	return (TRUE);
}

t_bool	entry_loop(t_queue *queue, DIR *dir, t_glob *glob)
{
	struct dirent	*entry;
	char			*full_path;

	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (!ms_match_pattern(entry, glob))
			continue ;
		full_path = ms_join_path(entry->d_name, glob);
		if (!ms_enqueue(queue, full_path))
			return (FALSE);
	}
	return (TRUE);
}

t_bool	ms_filename_expansion(t_queue *queue, char *str, t_env *env)
{
	extern int	errno;
	t_glob		*glob;
	DIR			*dir;
	t_bool		result;

	glob = ms_parse_glob(str);
	if (!glob)
		return (FALSE);
	if (*(glob->path) == '\0')
		dir = opendir(".");
	else
		dir = opendir(glob->path);
	if (!dir && errno != ENOENT)
		return (FALSE);
	if (errno == ENOENT)
	{
		if (!ms_enqueue(queue, ft_strdup(str)))
			return (FALSE);
		ms_destroy_glob(glob);
		return (TRUE);
	}
	result = entry_loop(queue, dir, glob);
	closedir(dir);
	ms_destroy_glob(glob);
	return (result);
}
