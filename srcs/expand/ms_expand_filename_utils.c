#include "libft.h"
#include "ms_expand.h"
#include <fcntl.h>
#include <unistd.h>

static t_bool	is_exist(char *str);

void	inspect_filename(t_queue *queue)
{
	t_list	*node;
	t_list	*tmp;

	if (queue->size == 0)
		return ;
	node = queue->head;
	while (node)
	{
		tmp = node->next;
		if (!is_exist(node->content))
			ms_pick_queue(queue, node);
		node = tmp;
	}
}

static t_bool	is_exist(char *str)
{
	DIR		*dir;
	int		fd;
	t_bool	result;

	dir = opendir(str);
	fd = open(str, O_RDONLY);
	result = FALSE;
	if (dir || fd >= 0)
		result = TRUE;
	if (fd >= 0)
		close(fd);
	if (dir)
		closedir(dir);
	return (result);
}

char	**no_match(char *str)
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
