/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:22:25 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:47:29 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*node;

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
