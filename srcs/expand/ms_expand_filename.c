#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"
#include <dirent.h>

static t_bool	expand_loop_inner(t_queue *queue, int size, t_env *env);
static size_t	get_max_depth(char *str);
static char		**expansion_failed(char *str);

/**
* @details filename expansion\n
* - `*`를 제외한 다른 특수 패턴을 처리하지 않습니다.
* @see https://runebook.dev/ko/docs/bash/pattern-matching
 */
char	**ms_expand_filename(char **argv, t_env *env)
{
	t_queue	*queue;
	char	**expanded;
	char	**new_argv;

	queue = ms_init_queue();
	if (!queue)
		return (NULL);
	new_argv = NULL;
	while (*argv)
	{
		expanded = ms_expand_loop(queue, *argv, env);
		if (!expanded
			|| !ms_strsjoin(&new_argv, expanded))
		{
			ms_destroy_queue(queue);
			return (NULL);
		}
		ms_clear_queue(queue);
		argv++;
	}
	ms_destroy_queue(queue);
	return (new_argv);
}

char	**ms_expand_loop(t_queue *queue, char *str, t_env *env)
{
	size_t	max_depth;
	size_t	depth;
	int		size;
	char	*tmp;

	tmp = ft_strdup(str);
	if (!tmp)
		return (NULL);
	if (!ms_enqueue(queue, tmp))
		return (NULL);
	depth = 0;
	max_depth = get_max_depth(str);
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

	while (size--)
	{
		node = ms_dequeue(queue);
		if (!node)
			break ;
		result = ms_filename_expansion(queue, node->content, env);
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

	expanded = (char **)malloc(sizeof(char *) + 2);
	if (!expanded)
		return (NULL);
	expanded[0] = ft_strdup(str);
	if (!expanded[0])
	{
		free(expanded);
		return (NULL);
	}
	expanded[1] = NULL;
	return (expanded);
}
