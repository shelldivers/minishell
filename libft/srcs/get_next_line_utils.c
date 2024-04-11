/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:06:41 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/01/05 18:48:12 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

char	*ft_content_sub(t_gnl *node, unsigned int start, long len)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * node->size);
	if (!str)
		return (0);
	ft_strncpy(str, (node->content) + start, len);
	return (str);
}

static char	*ft_content_concat(t_gnl *node, char *buf, long res)
{
	char	*str;
	long	size;

	if (node->content && node->size > node->length + res)
	{
		ft_strncpy((node->content) + node->length, buf, res);
		node->length += res;
		return (node->content);
	}
	size = node->size * 2;
	if (size < node->length + res)
		size = node->length + res;
	str = (char *)malloc(sizeof(char) * (size));
	if (!str)
		return (0);
	ft_strncpy(str, node->content, node->length);
	ft_strncpy(str + node->length, buf, res);
	free(node->content);
	node->content = str;
	node->length += res;
	node->size = size;
	return (node->content);
}

long	read_content_stack(t_gnl *node)
{
	char	buf[BUFFER_SIZE];
	long	res;
	char	*content;

	res = read(node->fd, buf, sizeof(char) * BUFFER_SIZE);
	if (res > 0)
	{
		content = ft_content_concat(node, buf, res);
		if (!content)
			return (-1);
	}
	return (res);
}

long	read_content_heap(t_gnl *node)
{
	char	*buf;
	long	res;
	char	*content;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (-1);
	res = read(node->fd, buf, sizeof(char) * BUFFER_SIZE);
	if (res > 0)
	{
		content = ft_content_concat(node, buf, res);
		if (!content)
		{
			free(buf);
			return (-1);
		}
	}
	free(buf);
	return (res);
}
