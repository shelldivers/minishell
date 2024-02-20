/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_strs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:22:25 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:37 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

void	strs_add_back(t_strs **lst, t_strs *new_node)
{
	t_strs	*node;

	if (lst == 0 || new_node == 0)
		return ;
	node = *lst;
	if (!node)
		*lst = new_node;
	else
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
}

void	strs_clear(t_strs **lst)
{
	t_strs	*node;
	t_strs	*next;

	if (!lst)
		return ;
	node = *lst;
	while (node)
	{
		next = node->next;
		free(node->content);
		free(node);
		node = next;
	}
	*lst = 0;
}

t_strs	*strs_new(char *content, int size)
{
	t_strs	*node;

	node = (t_strs *)malloc(sizeof(t_strs));
	if (!node)
		return (0);
	node->content = content;
	node->size = size;
	node->next = NULL;
	return (node);
}
