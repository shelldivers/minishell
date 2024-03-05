#include "libft.h"
#include "ms_env.h"
#include <stdlib.h>

/**
 * @errno ENOMEM
 */
t_bool	ms_expand_env_exchange(char **str, int *index, char *value)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strndup(*str, *index);
	if (tmp == NULL)
		return (FALSE);
	tmp2 = ft_strjoin(tmp, value);
	free(tmp);
	if (tmp2 == NULL)
		return (FALSE);
	*index = (int)ft_strlen(tmp2);
	tmp = ft_strjoin(tmp2, *str + *index);
	free(tmp2);
	if (tmp == NULL)
		return (FALSE);
	free(*str);
	*str = tmp;
	return (TRUE);
}

/**
 * @errno ENOMEM
 */
t_bool	ms_expand_env(char **str, int *index, t_env **env)
{
	int		i;
	char	*key;
	char	*value;

	i = *index;
	ft_memmove((*str) + i, (*str) + i + 1, ft_strlen((*str) + i));
	while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == '_'))
		i++;
	key = ft_substr(*str, *index, i - *index);
	if (key == NULL)
		return (FALSE);
	value = ms_getenv(*env, key);
	free(key);
	if (value == NULL)
		value = "";
	if (!ms_expand_env_exchange(str, index, value))
		return (FALSE);
	return (TRUE);
}

void	ms_expand_escape(char *arg, int *index)
{
	int	i;

	i = *index;
	ft_memmove(arg + i, arg + i + 1, ft_strlen(arg + i));
	*index += 1;
}

void	ms_expand_quote(char *arg, int *index)
{
	int		i;

	i = *index;
	ft_memmove(arg + i, arg + i + 1, ft_strlen(arg + i));
	while (arg[i] && arg[i] != '\'')
		i++;
	if (arg[i] == '\'')
		ft_memmove(arg + i, arg + i + 1, ft_strlen(arg + i));
	*index = i;
}

void	ms_expand_dquote(char *arg, int *index, t_env **env)
{
	int	i;

	i = *index;
	ft_memmove(arg + i, arg + i + 1, ft_strlen(arg + i));
	while (arg[i] && arg[i] != '\"')
	{
		if (arg[i] == '\\')
			ms_expand_escape(arg, &i);
		else if (arg[i] == '$')
			ms_expand_env(&arg, &i, env);
		else
			i++;
	}
	if (arg[i] == '\"')
		ft_memmove(arg + i, arg + i + 1, ft_strlen(arg + i));
	*index = i;
}
