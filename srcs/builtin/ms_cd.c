#include "libft.h"
#include "ms_builtin.h"
#include "ms_env.h"
#include <string.h>
#include <unistd.h>

static t_bool	ms_chdir(char *path, t_env **env)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		old_pwd = "";
	if (chdir(path) == -1)
		return (FALSE);	// error message
	if (!ms_setenv(env, OLDPWD, old_pwd))
		return (FALSE);	// error message
	pwd = getcwd(NULL, 0);
	if (!ms_setenv(env, PWD, pwd))
		return (FALSE);	// error message
	return (TRUE);
}

static int	ms_cd_home(t_env **env)
{
	char	*path;

	path = ms_getenv(*env, HOME);
	if (!path)
		return (EXIT_FAILURE);	// error message
	if (!ms_chdir(path, env))
		return (EXIT_FAILURE);	// error message
	return (EXIT_SUCCESS);
}

static int	ms_cd_tilde(char *argv, t_env **env)
{
	char	*home;
	char	*path;
	t_bool	result;

	home = ms_getenv(*env, HOME);
	if (!home)
		return (EXIT_FAILURE);	// error message
	path = ft_strjoin(home, argv + 1);
	if (!path)
		return (EXIT_FAILURE);	// error message
	result = ms_chdir(path, env);
	free(path);
	if (!result)
		return (EXIT_FAILURE);	// error message
	return (EXIT_SUCCESS);
}

int	ms_cd(int argc, char **argv, t_env **env)
{
	if (argc < 1 || argv == NULL || env == NULL)
		return (EXIT_FAILURE);	// error message
	if (argc == 1 || argv[1] == NULL)
		return (ms_cd_home(env));
	if (*argv[1] == '~' && *(argv[1] + 1) == '\0')
		return (ms_cd_home(env));
	if (*argv[1] == '~' && *(argv[1] + 1) == '/')
		return (ms_cd_tilde(argv[1], env));
	if (!ms_chdir(argv[1], env))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
