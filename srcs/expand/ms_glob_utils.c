#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"

t_bool	ms_parse_glob(t_glob *glob, char *str)
{
	char	*pos;
	t_bool	quote;
	t_bool	dquote;

	quote = FALSE;
	dquote = FALSE;
	pos = str;
	while (*pos)
	{
		if (!dquote && *pos == '\'')
		{
			quote = (t_bool) !quote;
			ft_memmove(pos, pos + 1, ft_strlen(pos) + 1);
		}
		else if (!quote && *pos == '\"')
		{
			dquote = (t_bool) !dquote;
			ft_memmove(pos, pos + 1, ft_strlen(pos) + 1);
		}
		else if (!quote && !dquote && *pos == '*')
			return (ms_parse_patterns(glob, str, pos));
		else
			pos++;
	}
	return (TRUE);
}
