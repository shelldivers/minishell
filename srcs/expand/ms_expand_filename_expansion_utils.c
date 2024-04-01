#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"
#include <dirent.h>

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

t_bool	ms_match_pattern(char *d_name, t_glob *glob)
{
	t_list	*node;
	char	*pat;

	node = glob->pattern->head;
	while (node && *d_name)
	{
		pat = node->content;
		if (!pat)
			return (TRUE);
		if (*pat != '\0')
		{
			while (node != glob->pattern->head && *d_name && *d_name != *pat)
				d_name++;
			while (*d_name && *pat && *d_name == *pat)
			{
				d_name++;
				pat++;
			}
			if (*pat != '\0')
				return (FALSE);
		}
		node = node->next;
	}
	return (TRUE);
}

t_bool	ms_match_type(struct dirent *entry, t_glob *glob)
{
	if (ft_strcmp(entry->d_name, ".") == 0)
		return (FALSE);
	if (ft_strcmp(entry->d_name, "..") == 0)
		return (FALSE);
	if (*(glob->remain) == '/' && entry->d_type != DT_DIR)
		return (FALSE);
	if (*(glob->content) != '.' && *(entry->d_name) == '.')
		return (FALSE);
	return (TRUE);
}
