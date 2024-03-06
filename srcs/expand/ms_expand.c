#include "ms_expand.h"
#include "ms_error.h"

static t_bool	ms_expand_handler(t_list **head, t_list **node, t_env **env);
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
	new_argv = ms_expand_transform_free(head);
	if (!new_argv)
	{
		ms_puterror_arg(*env, *argv);
		ft_lstclear(head, free);
		free(head);
		return (NULL);
	}
	return (new_argv);
}

t_bool	ms_expand_proceed(t_list **head, t_env **env)
{
	t_list	*node;

	node = *head;
	while (node)
	{
		if (!ms_expand_handler(head, &node, env))
		{
			ms_puterror_arg(*env, node->content);
			ft_lstclear(head, free);
			return (FALSE);
		}
		if (!node)
			break ;
		node = node->next;
	}
	return (TRUE);
}

t_bool	ms_wildcard_is_valid(t_list *node)
{
	if (!node)
		return (FALSE);
	if (ft_strchr(node->content, '*') != NULL)
		return (FALSE);
	return (TRUE);
}

/**
 * @errno ENOMEM
 */
static t_bool	ms_expand_handler(t_list **head, t_list **node, t_env **env)
{
	int		i;
	void	*f;
	t_list	**tmp;
	t_list	**next;

	i = 0;
	while (*node && ((char *)(*node)->content)[i] && i != -1)
	{
		f = ms_expand_dispatcher(((char *)(*node)->content)[i]);
		if (f == (void *)0)
			i++;
		else if (f == (void *)1)
		{
			tmp = ms_expand_wildcard(node, env);
			if (!tmp)
				return (FALSE);
			if (!ms_wildcard_is_valid(*tmp))
			{
				ft_lstclear(tmp, free);
				free(tmp);
				i++;
			}
			else
			{
				/**
				 * 여기서 현재 노드를 전달해야함
				 */
				*node = ms_wildcard_replace(head, node, tmp);
				free(tmp);
				i = 0;
			}
		}
		else
		{
			if (!((t_bool(*)(t_list **, t_list **, int *, t_env **))f)
					(head, node, &i, env))
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
		return ((void *)1);
	else
		return ((void *)0);
}
