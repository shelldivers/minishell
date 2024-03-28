#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"

t_bool	ms_get_path(t_glob *glob, char *str)
{
	char	*pat;
	char	*path;
	int		is_root;

	is_root = 0;
	while (str[is_root] && str[is_root] == '/')
		is_root++;
	pat = get_pat(str, is_root);
	if (!pat)
	{
		if (is_root == 1)
			path = ft_strdup("/");
		else
			path = ft_strdup("");
	}
	else
		path = ft_strndup(str, pat - str);
	if (!path)
		return (FALSE);
	glob->path = path;
	ms_dequote(glob->path, '\"');
	return (TRUE);
}

t_bool	ms_get_pattern(t_glob *glob, char *str) // TODO : Failed to parse pattern
{
	char	*glob_pos;
	char	*glob_start;
	char	*glob_end;

	glob_pos = get_glob_pos(str);
	if (!glob_pos)
	{
		glob->pattern = ft_strdup("");
		return (TRUE);
	}
	glob_start = get_glob_start(str, glob_pos);
	glob_end = get_glob_end(glob_pos);
	glob->pattern = ft_strndup(glob_start, glob_end - glob_start);
	if (!glob->pattern)
		return (FALSE);
	return (TRUE);
}

t_bool	ms_get_remain(t_glob *glob, char *str)
{
	char	*pos;
	char	*remain;

	pos = get_glob_pos(str);
	if (!pos)
	{
		glob->remain = ft_strdup("");
		return (TRUE);
	}
	remain = ft_strchr(pos, '/');
	if (!remain)
		remain = ft_strdup("");
	else
		remain = ft_strdup(remain);
	if (!remain)
		return (FALSE);
	glob->remain = remain;
	return (TRUE);
}
