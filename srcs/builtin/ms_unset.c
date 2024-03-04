#include "ms_builtin.h"
#include "ms_env.h"
#include "ms_error.h"
#include <stdlib.h>

int	ms_unset(int argc, char **argv, t_env **env)
{
	int	status;

	if (argc == 1)
		return (EXIT_SUCCESS);
	argv++;
	status = EXIT_SUCCESS;
	while (*argv)
	{
		if (ms_is_valid_env_key(*argv) == FALSE)
		{
			ms_puterror_identifier(*env, "unset", *argv);
			status = EXIT_FAILURE;
		}
		else
			ms_env_remove(env, *argv);
		argv++;
	}
	return (status);
}
