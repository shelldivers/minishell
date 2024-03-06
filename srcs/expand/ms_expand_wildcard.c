#include "libft.h"
#include "ft_printf.h"
#include "ms_expand.h"
#include "ms_env.h"
#include <dirent.h>

/**
 * @errno EACCES
 * @errno EBADF
 * @errno EMFILE
 * @errno ENFILE
 * @errno ENOENT
 * @errno ENOMEM
 * @errno ENOTDIR
 */
t_bool	ms_expand_wildcard(t_list **lst, t_list *node, int *idx, t_env **env)
{
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(".");
	if (!dir)
		return (FALSE);
	dirent = readdir(dir);
	ft_printf("%s\n", dirent->d_name);
	closedir(dir);
}
