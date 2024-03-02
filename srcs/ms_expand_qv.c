#include "ms_expand.h"
#include <stdlib.h>

char	*ms_expand_qv_exchange(char *arg)
{
	int		i;

	if (arg == NULL)
		return (NULL);
	i = 0;
	while (arg[i] && i != -1)
	{
		if (arg[i] == '\'')
			ms_expand_quote(arg, &i);
		else if (arg[i] == '\"')
			ms_expand_dquote(arg, &i);
		else if (arg[i] == '\\')
			ms_expand_escape(arg, &i);
		else if (arg[i] == '$')
		{
			if (!ms_expand_env(&arg, &i))
				return (NULL);
		}
		else{}
			i++;
	}
	return (arg);
}

t_bool	ms_expand_qv(char **args)
{
	int		i;
	char	*tmp;

	if (args == NULL)
		return (FALSE);
	i = 0;
	while (args[i])
	{
		tmp = ms_expand_qv_exchange(args[i]);
		if (!tmp)
			return (FALSE);
		free(args[i]);
		args[i] = tmp;
		i++;
	}
	return (TRUE);
}