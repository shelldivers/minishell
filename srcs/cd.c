#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	cd_home(void)
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

int	cd_tilde(char *argv)
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

int	cd(int argc, char **argv)
{
	if (argc < 1 || argv == NULL)
		return (EXIT_FAILURE);	// todo : error message
	if (argc == 1 || argv[1] == NULL)
		return (cd_home());
	if (*argv[1] == '~' && *(argv[1] + 1) == '\0')
		return (cd_home());
	if (*argv[1] == '~' && *(argv[1] + 1) == '/')
		return (cd_tilde(argv[1]));
	if (chdir(argv[1]) == -1)
	{
		perror("cd");	// todo : error message
		return (errno);
	}
	return (EXIT_SUCCESS);
}
