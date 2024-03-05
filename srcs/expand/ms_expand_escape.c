#include "libft.h"
#include "ms_expand.h"

void	ms_expand_escape(char *str, int *index)
{
	int	i;

	i = *index;
	ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
	*index += 1;
}
