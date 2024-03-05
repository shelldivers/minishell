#include "libft.h"
#include "ms_env.h"
#include "ms_expand.h"

void	ms_expand_quote(char *str, int *index)
{
	int		i;

	i = *index;
	ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\'')
		ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
	*index = i;
}

void	ms_expand_dquote(char *str, int *index, t_env **env)
{
	int	i;

	i = *index;
	ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\\'))
			ms_expand_escape(str, &i);
		else if (str[i] == '$')
			ms_expand_env(&str, &i, env);
		else
			i++;
	}
	if (str[i] == '\"')
		ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
	*index = i;
}
