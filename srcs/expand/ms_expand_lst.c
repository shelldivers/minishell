#include "libft.h"
#include "ms_expand.h"

static t_list	*ms_expand_newlst(char *arg);

/**
 * @errno ENOMEM
 */
t_list	**ms_expand_init(char **argv)
{
	t_list	**head;
	t_list	*node;

	head = (t_list **)malloc(sizeof(t_list *));
	if (!head)
		return (NULL);
	*head = NULL;
	while (*argv)
	{
		node = ms_expand_newlst(*argv);
		if (!node)
		{
			ft_lstclear(head, free);
			free(head);
			return (NULL);
		}
		ft_lstadd_back(head, node);
		argv++;
	}
	return (head);
}

/**
 * @errno ENOMEM
 */
char	**ms_expand_transform(t_list **head)
{
	t_list	*node;
	char	**argv;
	size_t	size;
	size_t	i;

	size = ft_lstsize(*head);
	argv = (char **)malloc(sizeof(char *) * (size + 1));
	if (!argv)
		return (NULL);
	i = 0;
	node = *head;
	while (node)
	{
		argv[i] = (char *)node->content;
		node = node->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

void	ms_expand_node_clear(t_list **head)
{
	t_list	*node;
	t_list	*tmp;

	node = *head;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
	free(head);
}

/**
 * @errno ENOMEM
 */
static t_list	*ms_expand_newlst(char *arg)
{
	t_list	*node;
	char	*str;

	str = ft_strdup(arg);
	if (!str)
		return (NULL);
	node = ft_lstnew(str);
	if (!node)
	{
		free(str);
		return (NULL);
	}
	return (node);
}
