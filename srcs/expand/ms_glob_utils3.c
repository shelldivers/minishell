#include "ft_printf.h"
#include "libft.h"
#include "ms_expand.h"

static t_bool	ms_dquote_pattern(char *pos1, t_bool *quote, t_bool *dquote);
static t_bool	ms_enqueue_pattern(t_glob *glob, char *pos1, char *pos2);

t_bool	ms_parse_pattern(t_glob *glob)
{
	char	*dup;

	dup = ft_strdup(glob->content);
	if (!dup)
		return (FALSE);
	glob->pattern = ms_init_queue();
	if (!glob->pattern)
	{
		free(dup);
		return (FALSE);
	}
	if (!ms_enqueue_patterns(glob, dup))
	{
		ms_destroy_queue(glob->pattern);
		free(dup);
		return (FALSE);
	}
	free(dup);
	return (TRUE);
}

t_bool	ms_enqueue_patterns(t_glob *glob, char *pos1)
{
	char	*pos2;
	t_bool	quote;
	t_bool	dquote;

	quote = FALSE;
	dquote = FALSE;
	pos2 = pos1;
	while (*pos1)
	{
		if (ms_dquote_pattern(pos1, &quote, &dquote))
			continue ;
		else if (!quote && !dquote && *pos1 == '*')
		{
			if (!ms_enqueue_pattern(glob, pos1, pos2))
				return (FALSE);
			pos2 = ++pos1;
		}
		else
			pos1++;
	}
	if (pos1 != pos2)
		return (ms_enqueue_pattern(glob, pos1, pos2));
	else
		return (ms_enqueue(glob->pattern, ft_strdup("")));	// todo : check
}

static t_bool	ms_dquote_pattern(char *pos1, t_bool *quote, t_bool *dquote)
{
	if (!*dquote && *pos1 == '\'')
	{
		*quote = (t_bool) !*quote;
		ft_memmove(pos1, pos1 + 1, ft_strlen(pos1) + 1);
		return (TRUE);
	}
	else if (!*quote && *pos1 == '\"')
	{
		*dquote = (t_bool) !*dquote;
		ft_memmove(pos1, pos1 + 1, ft_strlen(pos1) + 1);
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	ms_enqueue_pattern(t_glob *glob, char *pos1, char *pos2)
{
	char	*pattern;

	pattern = ft_strndup(pos2, pos1 - pos2);
	if (!pattern)
		return (FALSE);
	if (!ms_enqueue(glob->pattern, pattern))
	{
		free(pattern);
		return (FALSE);
	}
	return (TRUE);
}
