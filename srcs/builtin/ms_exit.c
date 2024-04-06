/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:32:52 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/04 20:32:59 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_builtin.h"
#include "ms_error.h"
#include <stdlib.h>
#include <unistd.h>

static long long	is_negative(char **nbr)
{
	long long	n_flag;

	n_flag = 1;
	if (*(*nbr) == '+')
		(*nbr)++;
	else if (*(*nbr) == '-')
	{
		n_flag = -1;
		(*nbr)++;
	}
	return (n_flag);
}

static char	int64_to_int8(char *str)
{
	char		*nbr;
	long long	ac;
	long long	tmp;
	long long	n_flag;

	nbr = str;
	while ((*nbr >= 9 && *nbr <= 13) || *nbr == ' ')
		nbr++;
	n_flag = is_negative(&nbr);
	ac = 0;
	while (ft_isdigit(*nbr))
	{
		tmp = ac * 10 + (*nbr++ - '0') * n_flag;
		if ((n_flag == 1 && tmp < ac) || (n_flag == -1 && tmp > ac))
		{
			ms_puterror_numeric(NULL, "exit", str);
			return ((char)255);
		}
		ac = tmp;
	}
	return ((char) ac);
}

int	ms_exit(int argc, char **argv, t_env **env)
{
	(void)argc;
	argv++;
	write(1, "exit\n", 5);
	if (*argv == NULL)
		exit(EXIT_SUCCESS);
	if (ft_isnumeric(*argv) == 0)
	{
		ms_puterror_numeric(*env, "exit", *argv);
		exit(255);
	}
	if (*(argv + 1) != NULL)
	{
		ms_puterror_too_many_args(*env, "exit");
		return (EXIT_FAILURE);
	}
	exit(int64_to_int8(*argv));
}
