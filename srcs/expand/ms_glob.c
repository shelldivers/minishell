#include "libft.h"
#include "ms_expand.h"

t_glob	*ms_init_glob(char *str)
{
	t_glob	*glob;
	t_bool	result;
	char	*raw;

	raw = ft_strdup(str);
	if (!raw)
		return (NULL);
	glob = (t_glob *)malloc(sizeof(t_glob));
	if (!glob)
	{
		free(raw);
		return (NULL);
	}
	ft_memset(glob, 0, sizeof(t_glob));
	result = ms_parse_glob(glob, str);
	free(raw);
	if (!result)
		return (NULL);
	return (glob);
}

void	ms_destroy_glob(t_glob *glob)
{
	if (glob->path)
		free(glob->path);
	if (glob->content)
		free(glob->content);
	if (glob->remain)
		free(glob->remain);
	if (glob->pattern)
		ms_destroy_queue(glob->pattern);
	free(glob);
}
