#include "ms_expand.h"
#include "ms_error.h"

static t_bool	ms_expand_proceed(t_list **head, t_env **env);
static t_bool	ms_expand_handler(t_list **head, t_list *node, t_env **env);
static void		*ms_expand_dispatcher(char c);

char	**ms_expand(char **argv, t_env **env)
{
	t_list	**head;
	char	**new_argv;

	head = ms_expand_init(argv);
	if (!head)
	{
		ms_puterror_arg(*env, *argv);
		return (NULL);
	}
	if (!ms_expand_proceed(head, env))
	{
		free(head);
		return (NULL);
	}
	new_argv = ms_expand_transform(head);
	if (!new_argv)
	{
		ms_puterror_arg(*env, *argv);
		ft_lstclear(head, free);
		free(head);
		return (NULL);
	}
	ms_expand_node_clear(head);
	return (new_argv);
}

static t_bool	ms_expand_proceed(t_list **head, t_env **env)
{
	t_list	*node;

	node = *head;
	while (node)
	{
		if (!ms_expand_handler(head, node, env))
		{
			ms_puterror_arg(*env, node->content);
			ft_lstclear(head, free);
			return (FALSE);
		}
		node = node->next;
	}
	return (TRUE);
}

/**
 * @errno ENOMEM
 */
static t_bool	ms_expand_handler(t_list **head, t_list *node, t_env **env)
{
	int		i;
	t_bool	(*f)(t_list **, t_list *, int *, t_env **);

	i = 0;
	while (((char *)node->content)[i] && i != -1)
	{
		f = ms_expand_dispatcher(((char *)node->content)[i]);
		if (f == NULL)
			i++;
		else
		{
			if (!f(head, node, &i, env))
				return (FALSE);
		}
	}
	return (TRUE);
}

static void	*ms_expand_dispatcher(char c)
{
	if (c == '\'')
		return (ms_expand_quote);
	else if (c == '\"')
		return (ms_expand_dquote);
	else if (c == '\\')
		return (ms_expand_escape);
	else if (c == '$')
		return (ms_expand_env);
	else if (c == '*')
		return (ms_expand_wildcard);
	else
		return (NULL);
}