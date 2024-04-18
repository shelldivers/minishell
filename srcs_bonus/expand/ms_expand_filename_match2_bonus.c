/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filename_match2_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:53 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:31:21 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ms_expand_bonus.h"

static t_bool	dp_loop(const char *d_name, const char *pattern, t_table table);
static t_bool	init_table(char *d_name, char *pattern, t_table *table);
static void		destroy_table(t_table *table);

t_bool	match_pattern(char *d_name, char *pattern)
{
	t_table	table;
	t_bool	result;

	if (!init_table(d_name, pattern, &table))
		return (FALSE);
	table.arr[0][0] = 1;
	result = dp_loop(d_name, pattern, table);
	destroy_table(&table);
	return (result);
}

t_bool	dp_loop(const char *d_name, const char *pattern, t_table table)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (j <= table.y)
	{
		while (i <= table.x)
		{
			if (pattern[j - 1] == ASTERISK)
			{
				if (table.arr[j - 1][i] || (i > 0 && table.arr[j][i - 1]))
					table.arr[j][i] = 1;
			}
			else if (i == 0)
				table.arr[j][i] = 0;
			else if (table.arr[j - 1][i - 1] && d_name[i - 1] == pattern[j - 1])
				table.arr[j][i] = 1;
			i++;
		}
		j++;
		i = 0;
	}
	return ((t_bool) table.arr[table.y][table.x]);
}

static t_bool	init_table(char *d_name, char *pattern, t_table *table)
{
	int	i;

	table->x = (int) ft_strlen(d_name);
	table->y = (int) ft_strlen(pattern);
	table->arr = (int **)malloc(sizeof(int *) * (table->y + 1));
	if (!table->arr)
		return (FALSE);
	i = 0;
	while (i <= table->y)
	{
		table->arr[i] = (int *)malloc(sizeof(int) * (table->x + 1));
		if (!table->arr[i])
		{
			while (--i >= 0)
				free(table->arr[i]);
			return (FALSE);
		}
		ft_memset(table->arr[i], 0, sizeof(int) * (table->x + 1));
		i++;
	}
	return (TRUE);
}

static void	destroy_table(t_table *table)
{
	int	i;

	i = 0;
	while (i <= table->y)
		free(table->arr[i++]);
	free(table->arr);
}
