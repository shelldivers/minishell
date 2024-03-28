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
		if (!quote && !dquote && *str == '\"')
		{
			dquote = TRUE;
			str++;
		}
		else if (!quote && dquote && *str == '\"')
		{
			dquote = FALSE;
			str++;
		}
		else if (!dquote && !quote && *str == '\'')
		{
			quote = TRUE;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
		}
		else if (!dquote && quote && *str == '\'')
		{
			quote = FALSE;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
		}
		else
			str++;
	}
}

void	ms_remove_dquote(char *str)
{
	t_bool	dquote;

	dquote = FALSE;
	while (*str)
	{
		if (!dquote && *str == '\"')
		{
			dquote = TRUE;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
		}
		else if (dquote && *str == '\"')
		{
			dquote = FALSE;
			ft_memmove(str, str + 1, ft_strlen(str) + 1);
		}
		else
			str++;
	}
}
