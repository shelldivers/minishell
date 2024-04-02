/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filename_search.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/02 18:41:00 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_expand.h"

t_bool	ms_expand_filename_search(t_queue *queue, size_t size)
{
	t_list	*node;
	t_glob	*glob;
	t_bool	result;

	while (size--)
	{
		node = ms_dequeue(queue);
		glob = ms_init_glob(node->content);
		if (!glob)
			return (FALSE);
		result = ms_expand_filename_expand(queue, glob);
		ft_lstdelone(node, free);
		ms_destroy_glob(glob);
		if (!result)
			return (FALSE);
	}
	return (TRUE);
}
