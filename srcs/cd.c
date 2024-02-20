#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

int	cd(int argc, char **argv)
{
	char	*buf;

	// argv 가 없으면 홈 디렉토리로 이동
	buf = getcwd(NULL, 0);
	if (!buf)
		return (EXIT_FAILURE);
	free(buf);
	return (EXIT_SUCCESS);
}
