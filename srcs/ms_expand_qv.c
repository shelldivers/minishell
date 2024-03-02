#include "libft.h"
#include <stdlib.h>

void	ms_expand_escape(char *arg, int *index)
{
	int i;

	if (arg == NULL)
		return ;
	i = *index;
	ft_memmove(arg + i, arg + i + 1, ft_strlen(arg + i));
	*index += 1;
}

void	ms_expand_env(char *arg, int *index)
{
}

void	ms_expand_quote(char *arg, int *index)
{
	int		i;

	if (arg == NULL)
		return ;
	i = *index;
	ft_memmove(arg + i, arg + i + 1, ft_strlen(arg + i));
	while (arg[i] && arg[i] != '\'')
		i++;
	if (arg[i] == '\'')
		ft_memmove(arg + i, arg + i + 1, ft_strlen(arg + i));
	*index = i;
}

void	ms_expand_dquote(char *arg, int *index)
{
	int i;

	if (!arg)
		return ;
	i = *index;
	ft_memmove(arg + i, arg + i + 1, ft_strlen(arg + i));
	while (arg[i] && arg[i] != '\"')
	{
		if (arg[i] == '\\')
			ms_expand_escape(arg, &i);
		else if (arg[i] == '$')
			ms_expand_env(arg, &i);
		else
			i++;
	}
	if (arg[i] == '\"')
		ft_memmove(arg + i, arg + i + 1, ft_strlen(arg + i));
	*index = i;
}

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
		else if (arg[i] == '$')
			ms_expand_env(arg, &i);
		else if (arg[i] == '\\')
			ms_expand_escape(arg, &i);
		else
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