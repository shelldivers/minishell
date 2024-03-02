#include "ms_expand.h"
#include <stdlib.h>

char	**ms_expand(char **args)
{
	char	**new_args;

	if (args == NULL)
		return (NULL);
	if (!ms_expand_qv(args))
		return (NULL);
	new_args = ms_expand_aster(args);
	if (!new_args)
		return (NULL);
	return (new_args);
}