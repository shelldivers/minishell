#include "libft.h"
#include "ms_expand.h"

char	**ms_queue_to_array(t_queue *queue)
{
	char	**array;
	t_list	*node;
	size_t	i;

	array = (char **)malloc(sizeof(char *) * (queue->size + 1));
	if (!array)
		return (NULL);
	i = 0;
	node = queue->head;
	while (node)
	{
		array[i] = ft_strdup(node->content);
		if (!array[i])
		{
			while (i--)
				free(array[i]);
			free(array);
			return (NULL);
		}
		node = node->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}