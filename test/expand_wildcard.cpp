#include "ms_expand.h"
#include "ft_printf.h"
#include <dirent.h>
#include <sys/stat.h>
#include <gtest/gtest.h>

TEST(expand_wildcard, dirent)
{
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(".");
	if (!dir)
		return ;
	while (1)
	{
		dirent = readdir(dir);
		if (dirent == NULL)
			break ;
		ft_printf("%s\n", dirent->d_name);
	}
	closedir(dir);
}
