/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:48:15 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 17:35:28 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_error.h"
#include "ms_exec.h"
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

static void		ms_find_in_builtin(char **words, char **paths);
static void		ms_find_in_absolute(char **words);
static void		ms_exit_with_malloc(void);

void	ms_add_path(char **words, t_env **env)
{
	char		**envp;
	char		**paths;
	struct stat	buf;

	if (!ft_strlen(words[0]))
		return ;
	if (ft_strchr(words[0], '/'))
	{
		ms_find_in_absolute(words);
		return ;
	}
	stat(words[0], &buf);
	envp = ms_env_serialize(*env);
	paths = ms_get_paths(envp);
	ms_find_in_builtin(words, paths);
	ms_clear_sec_dimentional(envp);
	ms_clear_sec_dimentional(paths);
}

static void	ms_find_in_absolute(char **words)
{
	if (words[0][0] == '/')
		ms_check_path(words[0], words);
	else
	{
		if (!ms_find_in_current_path(words))
			ms_exit_with_malloc();
	}
}

static void	ms_find_in_builtin(char **words, char **paths)
{
	char	*added_path;

	if (!paths || !paths[0])
	{
		if (!ms_find_in_current_path(words))
			ms_exit_with_malloc();
		return ;
	}
	else
	{
		added_path = ms_change_to_absolute(paths, words);
		if (added_path)
		{
			ms_check_path(added_path, words);
			words[0] = added_path;
		}
		else
		{
			ms_puterror_no_command(words[0]);
			exit(127);
		}
	}
}

static	void	ms_exit_with_malloc(void)
{
	ms_puterror_cmd(NULL, "malloc");
	exit(1);
}
