#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ms_pwd(int argc, char **argv)
{
	char	*pwd;

	(void)argv;
	if (argc < 1)
		return (EXIT_FAILURE);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (EXIT_FAILURE);	// error message
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
