/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:37:40 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:47:45 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_next;
	void	*tmp;

	if (!lst || !f || !del)
		return (0);
	tmp = f(lst->content);
	new = ft_lstnew(tmp);
	if (!new)
		del(tmp);
	lst = lst->next;
	while (new && lst)
	{
		tmp = f(lst->content);
		new_next = ft_lstnew(tmp);
		if (!new_next)
		{
			del(tmp);
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&new, new_next);
		lst = lst->next;
	}
	return (new);
}
