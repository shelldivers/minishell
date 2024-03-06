#include "libft.h"
#include "ms_expand.h"

t_bool	ms_expand_escape(t_list **lst, t_list *node, int *idx, t_env **env)
{
	char	*str;
	int		i;

	(void)lst;
	(void)env;
	i = *idx;
	str = (char *)node->content;
	ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
	*idx += 1;
	return (TRUE);
}
