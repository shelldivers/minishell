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
#include "ft_printf.h"

static int	print_str(char *str, int length)
{
	int	ret;
	int	res;

	ret = 0;
	while (length > BUFFER_SIZE)
	{
		res = (int)write(1, str, sizeof(char) * BUFFER_SIZE);
		if (res < 0)
			return (-1);
		if (res == 0)
			return (ret);
		length -= res;
		ret += res;
		str += res;
	}
	res = (int)write(1, str, sizeof(char) * length);
	if (res < 0)
		return (-1);
	ret += res;
	return (ret);
}

static int	print_fmtlst(t_strs **head)
{
	t_strs		*node;
	int			ret;
	int			res;

	node = (*head)->next;
	ret = 0;
	while (node)
	{
		res = print_str(node->content, node->size);
		ret += res;
		if (res < 0 || ret < 0)
		{
			strs_clear(head);
			return (-1);
		}
		node = node->next;
	}
	strs_clear(head);
	return (ret);
}

int	ft_printf(const char *fmt, ...)
{
	t_strs	*head;
	va_list	ap;
	t_bool	res;
	int		ret;

	head = strs_new(NULL, 0);
	if (!head)
		return (-1);
	va_start(ap, fmt);
	res = get_fmtlst(&head, fmt, ap);
	va_end(ap);
	if (!res)
		return (-1);
	ret = print_fmtlst(&head);
	return (ret);
}
