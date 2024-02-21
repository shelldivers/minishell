#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ms_pwd(int argc, char **argv)
{
	char	*pwd;

	(void)argv;
	if (argc > 1)
	{
		// todo : error message
		return (EXIT_FAILURE);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
