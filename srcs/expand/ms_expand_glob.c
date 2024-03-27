#include "libft.h"
#include "ms_expand.h"

t_glob	*ms_parse_glob(char *str)
{
	t_glob	*glob;

	glob = ms_init_glob();
	if (!glob)
		return (NULL);
	if (!ms_get_path(glob, str)
		|| !ms_get_pattern(glob, str)
		|| !ms_get_remain(glob, str)
		|| !ms_parse_pattern(glob))
	{
		ms_destroy_glob(glob);
		return (NULL);
	}
	return (glob);
}

t_glob	*ms_init_glob(void)
{
	t_glob	*glob;

	glob = (t_glob *)malloc(sizeof(t_glob));
	if (!glob)
		return (NULL);
	ft_memset(glob, 0, sizeof(t_glob));
	return (glob);
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
