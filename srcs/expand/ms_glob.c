#include "libft.h"
#include "ms_expand.h"

t_glob	*ms_init_glob(char *str)
{
	t_glob	*glob;

	glob = (t_glob *)malloc(sizeof(t_glob));
	if (!glob)
		return (NULL);
	ft_memset(glob, 0, sizeof(t_glob));
	if (!ms_parse_glob(glob, str))
		return (NULL);
	return (glob);
}

t_bool	ms_parse_glob(t_glob *glob, char *str)
{
	if (!ms_get_path(glob, str)
		|| !ms_get_pattern(glob, str)
		|| !ms_get_remain(glob, str)
		|| !ms_parse_pattern(glob))
	{
		ms_destroy_glob(glob);
		return (FALSE);
	}
	return (TRUE);
}

void	ms_destroy_glob(t_glob *glob)
{
	if (glob->path)
		free(glob->path);
	if (glob->pattern)
		free(glob->pattern);
	if (glob->remain)
		free(glob->remain);
	if (glob->prefix)
		free(glob->prefix);
	if (glob->suffix)
		free(glob->suffix);
	free(glob);
}
