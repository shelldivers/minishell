#include "ms_expand.h"
#include "ms_error.h"

static t_bool	ms_expand_exchange(char **str, t_env **env);

t_bool	ms_expand(char **argv, t_env **env)
{
	while (*argv)
	{
		if (!ms_expand_exchange(argv, env))
		{
			ms_puterror_arg(*env, *argv);
			return (FALSE);
		}
		argv++;
	}
	return (TRUE);
}

/**
 * @errno ENOMEM
 */
static t_bool	ms_expand_exchange(char **str, t_env **env)
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
				return (FALSE);
		}
		else if ((*str)[i] == '*')
		{
			if (!ms_expand_wildcard(str, &i, env))
				return (FALSE);
		}
		else
			i++;
	}
	return (TRUE);
}