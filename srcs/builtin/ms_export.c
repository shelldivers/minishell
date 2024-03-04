#include "ms_builtin.h"
#include "ms_env.h"
#include "ms_error.h"
#include <unistd.h>

static t_bool	ms_export_env(t_env **env, char *str);

int	ms_export(int argc, char **argv, t_env **env)
{
	if (argc < 1 || argv == NULL || env == NULL)
		return (EXIT_FAILURE);	// error message
	if (argc == 1 || argv[1] == NULL)
	{
		ms_env_print_all(*env);
		return (EXIT_SUCCESS);
	}
	argv++;
	while (*argv)
	{
		ms_export_env(env, *argv);
		argv++;
	}
	return (EXIT_SUCCESS);
}

static t_bool	ms_export_env(t_env **env, char *str)
{
	t_env	*node;

	node = ms_str_to_env(str);
	if (!node)
		return (FALSE);
	if (!ms_setenv(env, node->key, node->value))
		ms_puterror_cmd_arg(*env, "export", node->key);
	free(node->key);
	free(node->value);
	free(node);
	return (TRUE);
}
