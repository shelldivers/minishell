/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:19:51 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:47:59 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static size_t	fmtlst_size(t_strs *const *head)
{
	t_strs		*node;
	size_t		len;

	len = 0;
	node = (*head)->next;
	while (node)
	{
		len += node->size;
		node = node->next;
	}
	return (len);
}

static char	*fmtlst_to_str(t_strs **head)
{
	char		*str;
	t_strs		*node;
	size_t		len;
	size_t		i;

	len = fmtlst_size(head);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	node = (*head)->next;
	i = 0;
	while (node)
	{
		ft_memcpy(str + i, node->content, node->size);
		i += node->size;
		node = node->next;
	}
	return (str);
}

char	*ft_sprintf(const char *fmt, ...)
{
	t_strs	*head;
	va_list	ap;
	t_bool	res;
	char	*str;

	head = strs_new(NULL, 0);
	if (!head)
		return (NULL);
	va_start(ap, fmt);
	res = get_fmtlst(&head, fmt, ap);
	va_end(ap);
	if (!res)
		return (NULL);
	str = fmtlst_to_str(&head);
	strs_clear(&head);
	return (str);
}
