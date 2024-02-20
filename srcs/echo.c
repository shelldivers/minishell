/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:21:48 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/02/20 17:21:49 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_bool.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_bool	is_option(char *str)
{
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		if (str[2] == '\0' || str[2] == ' ')
			return (TRUE);
	}
	return (FALSE);
}

int	echo(int argc, char **argv)
{
	int		i;
	t_bool	n_flag;

	if (argc < 1)
		return (EXIT_FAILURE);
	n_flag = is_option(argv[1]);
	i = 1;
	if (n_flag == TRUE)
		i++;
	while (i < argc)
		printf("%s ", argv[i++]);
	if (n_flag == TRUE)
		printf("\n");
	return (0);
}
