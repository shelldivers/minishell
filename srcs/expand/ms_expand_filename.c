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
	char	**tmp;
	int		i;

	queue = ms_init_queue();
	if (!queue)
		return (NULL);
	new_argv = NULL;
	while (*argv)
	{
		expanded = ms_expand_loop(queue, *argv, env);
		if (!expanded)
		{
			if (new_argv)
			{
				i = 0;
				while (new_argv[i])
					free(new_argv[i++]);
				free(new_argv);
			}
			ms_destroy_queue(queue);
			return (NULL);
		}
		tmp = ms_strsjoin(new_argv, expanded);
		if (!tmp)
		{
			if (new_argv)
			{
				while (*new_argv)
					free(*new_argv++);
				free(new_argv);
			}
			while (*expanded)
				free(*expanded++);
			free(expanded);
			ms_destroy_queue(queue);
			return (NULL);
		}
		if (new_argv)
			free(new_argv);
		free(expanded);
		new_argv = tmp;
		ms_clear_queue(queue);
		argv++;
	}
	ms_destroy_queue(queue);
	return (new_argv);
}
