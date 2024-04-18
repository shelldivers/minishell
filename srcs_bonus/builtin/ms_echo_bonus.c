/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:21:48 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:28:23 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtin_bonus.h"
#include "ft_bool.h"
#include <stdio.h>
#include <stdlib.h>

static t_bool	is_option(char *str)
{
	if (!str || *str != '-' || *(str + 1) == '\0')
		return (FALSE);
	str++;
	while (*str && *str == 'n')
		str++;
	if (*str == '\0')
		return (TRUE);
	return (FALSE);
}

int	ms_echo(int argc, char **argv, t_env **env)
{
	int	i;
	int	n_flag;

	(void)argc;
	(void)env;
	argv++;
	n_flag = 0;
	while (*argv && *argv[0] == '-')
	{
		if (!is_option(*argv))
			break ;
		n_flag++;
		argv++;
	}
	i = 0;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (EXIT_SUCCESS);
}
