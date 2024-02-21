#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	ms_cd_home(void)
{
	char		*path;

	path = getenv("HOME");
	if (!path)
	{
		write(2, "cd: HOME not set\n", 17);	// todo : error message
		return (EXIT_FAILURE);
	}
	if (chdir(path) == -1)
	{
		perror("cd");	// todo : error message
		return (errno);
	}
	return (EXIT_SUCCESS);
}

static int	ms_cd_tilde(char *argv)
{
	char	*path;

	path = ft_strjoin(getenv("HOME"), argv + 1);
	if (!path)
	{
		perror("cd");	// todo : error message
		return (EXIT_FAILURE);
	}
	if (chdir(path) == -1)
	{
		perror("cd");	// todo : error message
		return (errno);
	}
	free(path);
	return (EXIT_SUCCESS);
}

int	ms_cd(int argc, char **argv)
{
	if (argc < 1 || argv == NULL)
		return (EXIT_FAILURE);	// todo : error message
	if (argc == 1 || argv[1] == NULL)
		return (ms_cd_home());
	if (*argv[1] == '~' && *(argv[1] + 1) == '\0')
		return (ms_cd_home());
	if (*argv[1] == '~' && *(argv[1] + 1) == '/')
		return (ms_cd_tilde(argv[1]));
	if (chdir(argv[1]) == -1)
	{
		perror("cd");	// todo : error message
		return (errno);
	}
	return (EXIT_SUCCESS);
}
