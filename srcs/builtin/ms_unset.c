#include "minishell.h"
#include "ms_env.h"
#include <stdlib.h>
#include <unistd.h>

int	ms_unset(int argc, char **argv, t_env **env)
{
	int	status;

	if (argc < 1 || argv == NULL || env == NULL)
		return (EXIT_FAILURE);	// todo : error message
	if (argc == 1)
		return (EXIT_FAILURE); 	// todo : error message
	argv++;
	status = EXIT_SUCCESS;
	while (*argv)
	{
		if (ms_is_valid_env_key(*argv) == FALSE)
		{
			write(2, "unset: invalid parameter name\n", 30);	// todo : error message
			status = EXIT_FAILURE;
		}
		else
			ms_env_remove(env, *argv);
		argv++;
	}
	return (status);
}
