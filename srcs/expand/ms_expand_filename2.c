#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"
#include <dirent.h>
#include <errno.h>

t_bool	entry_loop(t_queue *queue, DIR *dir, t_glob *glob);
char	*join_path(char *entry, t_glob *glob);

t_bool	ms_filename_expansion(t_queue *queue, char *str, t_glob *glob)
{
	extern int	errno;
	DIR			*dir;
	t_bool		result;

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
		return (TRUE);
	}
	result = entry_loop(queue, dir, glob);
	closedir(dir);
	return (result);
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
		if (!ms_match_pattern(entry->d_name, glob)
			|| !ms_match_type(entry, glob))
			continue ;
		full_path = join_path(entry->d_name, glob);
		if (!ms_enqueue(queue, full_path))
			return (FALSE);
	}
	return (TRUE);
}

char	*join_path(char *entry, t_glob *glob)
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