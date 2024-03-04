#include "ms_builtin.h"
#include "ms_error.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	ms_pwd(int argc, char **argv, t_env **env)
{
	char	*pwd;

	(void)argv;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ms_puterror_cmd(*env, "pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
