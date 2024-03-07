/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:49:03 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/07 10:49:11 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
char	**ms_expand_transform_free(t_list **head)
{
	t_list	*node;
	t_list	*tmp;
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
		tmp = node->next;
		argv[i] = (char *)node->content;
		free(node);
		node = tmp;
		i++;
	}
	argv[i] = NULL;
	free(head);
	return (argv);
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
