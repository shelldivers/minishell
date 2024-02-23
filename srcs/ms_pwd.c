#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	ms_pwd(int argc, char **argv, char **envp)
{
	t_env	**env;
	char	*pwd;

	(void)argv;
	if (argc > 1)	// todo : error message
		return (EXIT_FAILURE);
	env = ms_env_deserialize(envp);
	if (!env)
		return (EXIT_FAILURE);	// todo : error message
	pwd = ms_getenv(*env, "PWD");
	if (!pwd)
	{
		ms_env_clear(env);
		return (EXIT_FAILURE);	// todo : error message
	}
	printf("%s\n", pwd);
	ms_env_clear(env);
	return (EXIT_SUCCESS);
}
