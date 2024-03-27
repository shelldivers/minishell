#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"
#include <dirent.h>
#include <errno.h>

t_bool	ms_match_pattern(char *d_name, t_glob *glob)
{
	size_t	prefix_len;
	size_t	suffix_len;

	prefix_len = ft_strlen(glob->prefix);
	suffix_len = ft_strlen(glob->suffix);
	if (ft_strncmp(d_name, glob->prefix, prefix_len) != 0)
		return (FALSE);
	if (ft_strcmp(d_name + ft_strlen(d_name) - suffix_len, glob->suffix) != 0)
		return (FALSE);
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
	if (*(glob->pattern) != '.' && *(entry->d_name) == '.')
		return (FALSE);
	return (TRUE);
}
