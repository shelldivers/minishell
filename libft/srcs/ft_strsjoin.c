#include "libft.h"
#include <stdlib.h>

static int	get_size(char **strs);
static void	free_strs(char **strs);
static void	move_strs(char **dest, char **s1, char **s2);

char	**ft_strsjoin(char ***dest, char **s2)
{
	char	**s1;
	char	**new_strs;
	size_t	i;
	size_t	j;

	s1 = *dest;
	i = get_size(s1);
	j = get_size(s2);
	new_strs = (char **)malloc(sizeof(char *) * (i + j + 1));
	if (new_strs)
	{
		move_strs(new_strs, s1, s2);
		*dest = new_strs;
	}
	free_strs(s1);
	free_strs(s2);
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

static void	free_strs(char **strs)
{
	while (strs && *strs)
		free(*strs++);
	free(strs);
}

static void	move_strs(char **dest, char **s1, char **s2)
{
	size_t	i;

	i = 0;
	while (s1 && *s1)
		dest[i++] = *s1++;
	while (s2 && *s2)
		dest[i++] = *s2++;
	dest[i] = NULL;
}
