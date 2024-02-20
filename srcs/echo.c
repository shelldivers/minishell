#include "minishell.h"
#include "ft_bool.h"
#include <stdio.h>
#include <stdlib.h>

t_bool	is_option(char *str)
{
	if (str[0] == '-')
		return (TRUE);
	return (FALSE);
}

int	echo(int argc, char **argv)
{
	if (argc < 1)
		return (EXIT_FAILURE);
	if (argc == 1)
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	return (0);
}