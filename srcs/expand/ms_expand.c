#include "ms_expand.h"
#include <stdlib.h>

char	**ms_expand(char **args, t_env **env)
{
	char	**new_args;

	if (!ms_expand_qv(args, env))
		return (NULL);
	new_args = ms_expand_aster(args, env);
	if (!new_args)
		return (NULL);
	return (new_args);
}