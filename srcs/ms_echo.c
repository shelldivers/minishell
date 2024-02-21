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

static t_bool	is_option(char *str)
{
	if (!str)
		return (FALSE);
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		if (str[2] == '\0' || str[2] == ' ')
			return (TRUE);
	}
	return (FALSE);
}

int	ms_echo(int argc, char **argv)
{
	int		i;
	t_bool	n_flag;

	if (argc < 1)	// todo : error message
		return (EXIT_FAILURE);
	n_flag = is_option(argv[1]);
	i = 1;
	if (n_flag == TRUE)
		i++;
	while (i < argc)
	{
		printf("%s", argv[i++]);
		if (i != argc)
			printf(" ");
	}
	if (n_flag == FALSE)
		printf("\n");
	return (EXIT_SUCCESS);
}
