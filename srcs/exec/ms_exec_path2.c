/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_path2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:48:15 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 19:01:44 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_error.h"
#include "ms_exec.h"
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

static	void	ms_exit_with_malloc(void);

void	ms_check_path(char *path, char **words)
{
	struct stat	buf;

	if (access(path, F_OK) == FAILED)
	{
		ms_puterror_no_file(words[0]);
		exit(127);
	}
	if (access(path, X_OK) == FAILED)
	{
		ms_puterror_permission_denied(words[0]);
		exit(126);
	}
	stat(path, &buf);
	if (s_isdir(buf.st_mode))
	{
		ms_puterror_is_dir(words[0]);
		exit(126);
	}
}

char	**ms_get_paths(char **envp)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strndup(envp[i] + 5, ft_strlen(envp[i]) - 5);
			if (!path)
				ms_exit_with_malloc();
			paths = ft_split(path, ':');
			free(path);
			if (!paths)
				ms_exit_with_malloc();
			return (paths);
		}
		i++;
	}
	return (NULL);
}

t_bool	ms_find_in_current_path(char **words)
{
	char	*path;
	char	*tmp;

	path = getcwd(NULL, 0);
	if (!path)
	{
		if (errno == EACCES)
		{
			ms_puterror_permission_denied(".");
			exit(126);
		}
		else if (errno == ENOMEM)
			return (FALSE);
	}
	tmp = ft_strjoin(path, "/");
	free(path);
	if (!tmp)
		return (FALSE);
	path = ft_strjoin(tmp, words[0]);
	free(tmp);
	if (!path)
		return (FALSE);
	ms_check_path(path, words);
	words[0] = path;
	return (TRUE);
}

char	*ms_change_to_absolute(char **paths, char **cmd_word)
{
	char	*path;
	char	*tmp;
	int		i;

	i = -1;
	while (paths && paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			ms_exit_with_malloc();
		tmp = ft_strjoin(path, *cmd_word);
		free(path);
		if (!tmp)
			ms_exit_with_malloc();
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
	}
	return (NULL);
}

static	void	ms_exit_with_malloc(void)
{
	ms_puterror_cmd(NULL, "malloc");
	exit(1);
}
