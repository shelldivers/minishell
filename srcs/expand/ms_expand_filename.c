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
