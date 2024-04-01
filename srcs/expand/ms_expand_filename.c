#include "ms_expand.h"
#include "libft.h"

static t_bool	init(t_queue *queue, char *str, int *depth, int *max_depth);
static int		get_max_depth(char *str);

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
	int		max_depth;
	t_bool	quote;
	t_bool	dquote;
	t_bool	path;

	path = TRUE;
	quote = FALSE;
	dquote = FALSE;
	max_depth = 0;
	while (*str)
	{
		if (*str == '/')
			path = TRUE;
		if (!dquote && *str == '\'')
			quote = (t_bool) !quote;
		else if (!quote && *str == '\"')
			dquote = (t_bool) !dquote;
		else if (!quote && !dquote && path && *str == '*')
		{
			path = FALSE;
			max_depth++;
		}
		str++;
	}
	return (max_depth);
}
