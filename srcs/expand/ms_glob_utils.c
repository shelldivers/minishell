#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"
#include <dirent.h>

static char		*get_pat(char *str, int is_root);

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

static char	*get_pat(char *str, int is_root)
{
	int		i;
	char	*pattern;
	t_bool	quote;

	quote = FALSE;
	pattern = NULL;
	i = is_root;
	while (str[i])
	{
		if (!quote && str[i] == '\"')
			quote = TRUE;
		else if (quote && str[i] == '\"')
			quote = FALSE;
		else if (str[i] == '/')
			pattern = str + i + 1;
		else if (!quote && str[i] == '*')
			break ;
		i++;
	}
	if (is_root > 0 && !pattern)
		pattern = str + is_root;
	return (pattern);
}
