#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"
#include <dirent.h>

static t_bool	expand_loop_inner(t_queue *queue, int size, t_env *env);
static size_t	get_max_depth(char *str);
static char		**expansion_failed(char *str);

char	**ms_expand_loop(t_queue *queue, char *str, t_env *env)
{
	size_t	max_depth;
	size_t	depth;
	int		size;
	char	*tmp;

	tmp = ft_strdup(str);
	if (!ms_enqueue(queue, tmp))
		return (NULL);
	depth = 0;
	max_depth = get_max_depth(str);	// @TODO: 수정 ms_filename_test15
	while (1)
	{
		size = (int)queue->size;
		if (size <= 0 || depth >= max_depth)
			break ;
		if (!expand_loop_inner(queue, size, env))
			return (NULL);
		depth++;
	}
	if (depth < max_depth || queue->size == 0)
		return (expansion_failed(str));
	return (ms_queue_to_array(queue));
}

static t_bool	expand_loop_inner(t_queue *queue, int size, t_env *env)
{
	t_list	*node;
	t_bool	result;
	t_glob	*glob;

	while (size--)
	{
		node = ms_dequeue(queue);
		if (!node)
			break ;
		glob = ms_parse_glob(node->content);
		if (!glob)
			return (FALSE);
		result = TRUE;
		if (*(glob->pattern) != '\0')
			result = ms_filename_expansion(queue, node->content, glob);
		ms_destroy_glob(glob);
		free(node->content);
		free(node);
		if (!result)
			return (FALSE);
	}
	return (TRUE);
}

static size_t	get_max_depth(char *str)
{
	size_t	max_depth;

	max_depth = 0;
	while (*str)
	{
		if (*str == '*')
			max_depth++;
		str++;
	}
	return (max_depth);
}

static char	**expansion_failed(char *str)
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
	ms_dequote(dequoted, '\"');
	expanded[0] = dequoted;
	expanded[1] = NULL;
	return (expanded);
}