/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:22:18 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/04 21:22:19 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtin.h"
#include "ms_env.h"
#include "ms_error.h"
#include <string.h>
#include <unistd.h>

static int		ms_cd_home(t_env **env);
static int		ms_cd_oldpwd(t_env **env);
static t_bool	ms_chdir(char *path, t_env **env);

/**
 * @notice `~` must be expaneded to the home directory
 */
int	ms_cd(int argc, char **argv, t_env **env)
{
	char	*path;

	if (argc == 1)
		return (ms_cd_home(env));
	path = *(++argv);
	if (*path == '-' && *(path + 1) == '\0')
		return (ms_cd_oldpwd(env));
	if (!ms_chdir(path, env))
	{
		ms_puterror_cmd_arg(*env, "cd", path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ms_cd_home(t_env **env)
{
	char	*path;

	path = ms_getenv(*env, HOME);
	if (!path)
	{
		ms_puterror_env_not_set(*env, "cd", HOME);
		return (EXIT_FAILURE);
	}
	if (!ms_chdir(path, env))
	{
		ms_puterror_cmd_arg(*env, "cd", path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ms_cd_oldpwd(t_env **env)
{
	char	*path;

	path = ms_getenv(*env, OLDPWD);
	if (!path)
	{
		ms_puterror_env_not_set(*env, "cd", OLDPWD);
		return (EXIT_FAILURE);
	}
	if (!ms_chdir(path, env))
	{
		ms_puterror_cmd_arg(*env, "cd", path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @errno ENOMEM
 * @errno EACCES
 * @errno EFAULT
 * @errno EIO
 * @errno ELOOP
 * @errno ENAMETOOLONG
 * @errno ENOENT
 * @errno ENOMEM
 * @errno ENOTDIR
 * @errno EACCES
 * @errno EBADF
 * @errno ENOTDIR
 */
static t_bool	ms_chdir(char *path, t_env **env)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		old_pwd = "";
	if (chdir(path) == -1)
		return (FALSE);
	if (!ms_setenv(env, OLDPWD, old_pwd))
		return (FALSE);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = path;
	if (!ms_setenv(env, PWD, pwd))
		return (FALSE);
	return (TRUE);
}
