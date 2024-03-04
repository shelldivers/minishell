#include "ms_builtin.h"
#include "ms_env.h"
#include <unistd.h>

static t_bool	ms_env_exec(char **argv, char **envp);

int	ms_env(int argc, char **argv, char **envp)
{
	t_env	**head;
	t_env	*env;

	if (argc < 1 || argv == NULL || envp == NULL)
		return (EXIT_FAILURE);	// todo : error message
	head = ms_env_deserialize(envp);
	if (head == NULL)
		return (EXIT_FAILURE);	// todo : error message
	while (*argv)
	{
		if (ms_is_valid_env_key(*argv) == FALSE)
			break ;
		env = ms_str_to_env(*argv);
		if (env == NULL)
			return (EXIT_FAILURE);	// todo : error message
		ms_env_push_back(head, env);
		argv++;
	}
	envp = ms_env_serialize(*head);
	ms_env_clear(head);
	// todo : ms_env_exec(argv, envp);
	return (EXIT_SUCCESS);
}

static t_bool	ms_env_exec(char **argv, char **envp)
{
	// todo : execve
}
