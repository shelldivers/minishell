#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"

static void	init(const char *str, char *pos, char **start, char **end);
static char	*ms_get_end(char *str);

t_bool	ms_parse_patterns(t_glob *glob, char *str, char *pos)
{
	char	*start;
	char	*end;

	init(str, pos, &start, &end);
	if (start - str > 0)
		glob->path = ft_strndup(str, start - str + 1);
	else
		glob->path = ft_strndup(str, start - str);
	if (!glob->path)
		return (FALSE);
	glob->remain = ft_strdup(end);
	if (!glob->remain)
		return (FALSE);
	if (*glob->path == '\0')
		glob->content = ft_strndup(start, end - start);
	else
		glob->content = ft_strndup(start + 1, end - start - 1);
	if (!glob->content)
		return (FALSE);
	if (!ms_parse_pattern(glob))
		return (FALSE);
	return (TRUE);
}

static char	*ms_get_end(char *str)
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
		else if (!quote && !dquote && *pos == '/')
			break ;
		else
			pos++;
	}
	return (pos);
}

static void	init(const char *str, char *pos, char **start, char **end)
{
	char	*_start;
	char	*next_pos;
	char	*_end;

	_start = pos;
	while (_start > str && *_start != '/')
		_start--;
	*start = _start;
	next_pos = ms_get_end(pos);
	if (*next_pos == '\0')
		*end = next_pos;
	else
	{
		_end = pos;
		while (_end <= next_pos && *_end != '/')
			_end++;
		*end = _end;
	}
}
