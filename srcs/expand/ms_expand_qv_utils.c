#include "libft.h"
#include <stdlib.h>

t_bool	ms_expand_env_exchange(char **arg, int *index, char *value)
{
	char	*tmp;
	char	*tmp2;

	if (arg == NULL || value == NULL)
		return (FALSE);
	tmp = ft_strndup(*arg, *index);
	if (tmp == NULL)
		return (FALSE);
	tmp2 = ft_strjoin(tmp, value);
	free(tmp);
	if (tmp2 == NULL)
		return (FALSE);
	*index = (int)ft_strlen(tmp2);
	tmp = ft_strjoin(tmp2, *arg + *index);
	free(tmp2);
	if (tmp == NULL)
		return (FALSE);
	free(*arg);
	*arg = tmp;
	return (TRUE);
}

t_bool	ms_expand_env(char **arg, int *index)
{
	int		i;
	char	*key;
	char	*value;

	if (arg == NULL)
		return (FALSE);
	i = *index;
	ft_memmove(arg + i, arg + i + 1, ft_strlen(*arg + i));
	while (arg[i] && (ft_isalnum(*arg[i]) || *arg[i] == '_'))
		i++;
	key = ft_substr(*arg, *index, i - *index);
	if (key == NULL)
		return (FALSE);
//	value = ms_getenv(key);	// todo: ms_getenv
	free(key);
	if (value == NULL)
		value = ft_strdup("");
	if (value == NULL)
		return (FALSE);
	ms_expand_env_exchange(arg, index, value);
	free(value);
	if (!arg)
		return (FALSE);
	return (TRUE);
}

void	ms_expand_escape(char *arg, int *index)
{
	int i;

	if (arg == NULL)
		return ;
	i = *index;
	ft_memmove(arg + i, arg + i + 1, ft_strlen(arg + i));
	*index += 1;
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
