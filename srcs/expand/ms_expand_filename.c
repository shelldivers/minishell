#include "ms_expand.h"
#include "libft.h"

static t_bool	init(t_queue *queue, char *str, int *depth, int *max_depth);
static int		get_max_depth(char *str);
static char		**no_match(char *str);

char	**ms_expand_filename(t_queue *queue, char *str)
{
	int		depth;
	int		max_depth;
	int		size;

	if (!init(queue, str, &depth, &max_depth))
		return (NULL);
	while (1)
	{
		size = (int)queue->size;
		if (size <= 0 || depth >= max_depth)
			break ;
		if (!ms_expand_filename_search(queue, size))
			return (NULL);
		depth++;
	}
	if (depth < max_depth || queue->size == 0)
		return (no_match(str));
	inspect_filename(queue);
	if (queue->size == 0)
		return (no_match(str));
	return (ms_queue_to_arrays(queue));
}

static t_bool	init(t_queue *queue, char *str, int *depth, int *max_depth)
{
	char	*tmp;

	tmp = ft_strdup(str);
	if (!tmp)
		return (FALSE);
	if (!ms_enqueue(queue, tmp))
		return (FALSE);
	*depth = 0;
	*max_depth = get_max_depth(str);
	return (TRUE);
}

static int	get_max_depth(char *str)
{
	int	max_depth;

	max_depth = 0;
	while (*str)
	{
		if (*str == '*')
			max_depth++;
		str++;
	}
	return (max_depth);
}

static char	**no_match(char *str)
{
	char	**expanded;
	char	*dequoted;

	expanded = (char **)malloc(sizeof(char *) + 2);
	if (!expanded)
		return (NULL);
	dequoted = ft_strdup(str);
	if (!dequoted)
	{
		free(expanded);
		return (NULL);
	}
	ms_remove_dquote(dequoted);
	expanded[0] = dequoted;
	expanded[1] = NULL;
	return (expanded);
}
