#include "ms_expand.h"
#include "ms_error.h"
#include <stdlib.h>

/**
 * @errno ENOMEM
 */
char	*ms_expand_qv_exchange(char **str, t_env **env)
{
	int		i;

	i = 0;
	while ((*str)[i] && i != -1)
	{
		if ((*str)[i] == '\'')
			ms_expand_quote(*str, &i);
		else if ((*str)[i] == '\"')
			ms_expand_dquote(*str, &i, env);
		else if ((*str)[i] == '\\')
			ms_expand_escape(*str, &i);
		else if ((*str)[i] == '$')
		{
			if (!ms_expand_env(str, &i, env))
				return (NULL);
		}
		else
			i++;
	}
	return (*str);
}

t_bool	ms_expand_qv(char **args, t_env **env)
{
	while (*args)
	{
		ms_expand_qv_exchange(args, env);
		if (!*args)
		{
			ms_puterror_arg(*env, *args);
			return (FALSE);
		}
		args++;
	}
	return (TRUE);
}
