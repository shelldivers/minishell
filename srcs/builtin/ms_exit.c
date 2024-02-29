#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	ms_exit(int argc, char **argv)
{
	char	exit_code;

	if (argc < 1)
		exit(0);
	if (argc > 2)
	{
		write(2, "exit: too many arguments\n", 25);	// todo : error message
		return (EXIT_FAILURE);
	}
	exit_code = 0;
	if (*(++argv) != NULL)
		exit_code = (char) ft_atoi(*argv);
	exit(exit_code);
}
