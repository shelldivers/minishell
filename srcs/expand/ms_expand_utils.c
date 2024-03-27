#include "libft.h"
#include "ms_expand.h"
#include <stdlib.h>

static int	get_size(char **strs);

void	ms_dequote(char *str, char ch)
{
	t_bool	quote;

	quote = FALSE;
	while (*str)
	{
		if (!quote && *str == ch)
		{
			quote = TRUE;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
		}
		else if (quote && *str == ch)
		{
			quote = FALSE;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
		}
		else
			str++;
	}
}

char	**ms_strsjoin(char **s1, char **s2)
{
	char	**new_strs;
	size_t	s1_len;
	size_t	s2_len;
	int		i;

	s1_len = get_size(s1);
	s2_len = get_size(s2);
	new_strs = (char **)malloc(sizeof(char *) * (s1_len + s2_len + 1));
	if (!new_strs)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		new_strs[i++] = *s1++;
	while (s2 && *s2)
		new_strs[i++] = *s2++;
	new_strs[s1_len + s2_len] = NULL;
	return (new_strs);
}

static int	get_size(char **strs)
{
	int	size;

	size = 0;
	while (strs && strs[size])
		size++;
	return (size);
}
