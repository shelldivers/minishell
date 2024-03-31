#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"

static t_bool	init(t_queue *queue, t_list **node, t_glob **glob);
static void		finalize(t_glob *glob, t_list *node);
static t_bool	quit(t_glob *glob, t_list *node);

t_bool	ms_expand_filename_search(t_queue *queue, int size)
{
	t_list	*node;
	t_glob	*glob;

	while (size--)
	{
		if (!init(queue, &node, &glob))
			return (quit(NULL, NULL));
		if (*(glob->content) == '\0')
		{
			finalize(glob, node);
			continue ;
		}
		if (!ms_expand_filename_expansion(queue, glob, node->content))
			return (quit(glob, node));
		finalize(glob, node);
	}
	return (TRUE);
}

static t_bool	init(t_queue *queue, t_list **node, t_glob **glob)
{
	t_list	*_node;
	t_glob	*_glob;

	_node = ms_dequeue(queue);
	if (!_node)
		return (FALSE);
	_glob = ms_init_glob(_node->content);
	if (!_glob)
	{
		free(_node->content);
		free(_node);
		return (FALSE);
	}
	*glob = _glob;
	*node = _node;
	return (TRUE);
}

static void	finalize(t_glob *glob, t_list *node)
{
	ms_destroy_glob(glob);
	free(node->content);
	free(node);
}

static t_bool	quit(t_glob *glob, t_list *node)
{
	if (glob)
		ms_destroy_glob(glob);
	if (node)
	{
		free(node->content);
		free(node);
	}
	return (FALSE);
}
