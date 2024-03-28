#include "libft.h"
#include "ms_expand.h"

void	ms_remove_quote(char *str)
{
	t_bool	dquote;
	t_bool	quote;

	dquote = FALSE;
	quote = FALSE;
	while (*str)
	{
		if (!quote && *str == '\"')
			dquote = (t_bool) !dquote;
		else if (!dquote && *str == '\'')
		{
			quote = (t_bool) !quote;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
			continue ;
		}
		str++;
	}
}

void	ms_remove_dquote(char *str)
{
	t_bool	dquote;
	t_bool	quote;

	dquote = FALSE;
	quote = FALSE;
	while (*str)
	{
		if (!quote && *str == '\"')
		{
			dquote = (t_bool) !dquote;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
			continue ;
		}
		else if (!dquote && *str == '\'')
			quote = (t_bool) !quote;
		str++;
	}
}
