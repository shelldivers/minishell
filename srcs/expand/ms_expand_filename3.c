#include "ms_expand.h"
#include "libft.h"
#include "ms_env.h"
#include <dirent.h>
#include <errno.h>

static t_bool	ms_match_filename(struct dirent *entry, t_glob *glob);
static t_bool	init(t_queue *queue, t_glob *glob, char *str, DIR **dir);
static void		finalize(DIR *dir);
static t_bool	quit(DIR *dir);

t_bool	ms_filename_expansion(t_queue *queue, t_glob *glob, char *str)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*path;

	if (!init(queue, glob, str, &dir))
		return (FALSE);
	while (dir)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (!ms_match_filename(entry, glob))
			continue ;
		path = join_path(entry->d_name, glob);
		if (!ms_enqueue(queue, path))
			return (quit(dir));
	}
	finalize(dir);
	return (TRUE);
}

static t_bool	ms_match_filename(struct dirent *entry, t_glob *glob)
{
	if (!ms_match_pattern(entry->d_name, glob))
		return (FALSE);
	if (!ms_match_type(entry, glob))
		return (FALSE);
	return (TRUE);
}

static	t_bool	init(t_queue *queue, t_glob *glob, char *str, DIR **dir)
{
	DIR			*_dir;

	if (*(glob->path) == '\0')
		_dir = opendir(".");
	else
		_dir = opendir(glob->path);
	if (!_dir && errno != ENOENT)
		return (FALSE);
	if (!_dir && errno == ENOENT)
	{
		if (!ms_enqueue(queue, ft_strdup(str)))
			return (FALSE);
	}
	*dir = _dir;
	return (TRUE);
}

static	void	finalize(DIR *dir)
{
	if (dir)
		closedir(dir);
}

static	t_bool	quit(DIR *dir)
{
	if (dir)
		closedir(dir);
	return (FALSE);
}
