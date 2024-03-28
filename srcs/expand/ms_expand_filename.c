#include "ms_expand.h"
#include "ms_env.h"
#include <dirent.h>

static t_bool	init(t_queue **queue, t_queue **expanded);
static void		finalize(t_queue **queue, t_queue **expanded);
static void		*quit(t_queue **queue, t_queue **expanded);

/**
* @details filename expansion\n
* - `*`를 제외한 다른 특수 패턴을 처리하지 않습니다.
* @see https://runebook.dev/ko/docs/bash/pattern-matching
 */
char	**ms_expand_filenames(char **argv, t_env *env)
{
	t_queue	*queue;
	t_queue	*expanded;
	char	**arrays;

	if (!init(&queue, &expanded))
		return (quit(NULL, NULL));
	while (*argv)
	{
		arrays = ms_expand_filename(queue, *argv);
		if (!arrays)
			return (quit(&queue, &expanded));
		ms_enqueue_arrays(expanded, arrays);
		ms_clear_queue(queue);
		argv++;
	}
	arrays = ms_queue_to_arrays(expanded);
	finalize(&queue, &expanded);
	return (arrays);
}

static t_bool	init(t_queue **queue, t_queue **expanded)
{
	t_queue	*_queue;
	t_queue	*_expanded;

	_queue = ms_init_queue();
	if (!_queue)
		return (FALSE);
	_expanded = ms_init_queue();
	if (!_expanded)
	{
		ms_destroy_queue(_queue);
		return (FALSE);
	}
	*queue = _queue;
	*expanded = _expanded;
	return (TRUE);
}

static void	finalize(t_queue **queue, t_queue **expanded)
{
	ms_destroy_queue(*queue);
	ms_destroy_queue(*expanded);
}

static void	*quit(t_queue **queue, t_queue **expanded)
{
	if (queue)
		ms_destroy_queue(*queue);
	if (expanded)
		ms_destroy_queue(*expanded);
	return ((void *)0);
}
