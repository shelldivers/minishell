/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:48:15 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/04 20:49:38 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "ms_minishell.h"

static char		**ms_get_paths(char **envp);
static char		*ms_change_to_absolute(char **paths, char **cmd_word);
static t_bool	ms_is_dir(struct stat buf, char **words);

void	ms_add_path(char **words, t_env **env)
{
	char		*add_path;
	char		**envp;
	char		**paths;
	struct stat	buf;

	stat(words[0], &buf);
	if (ms_is_dir(buf, words))
		return ;
	envp = ms_env_serialize(*env);
	paths = ms_get_paths(envp);
	add_path = ms_change_to_absolute(paths, words);
	if (!add_path)
	{
		ms_puterror_no_command(words[0]);
		exit(127);
	}
	ms_clear_sec_dimentional(envp);
	ms_clear_sec_dimentional(paths);
	if (stat(add_path, &buf) == 0 && S_ISDIR(buf.st_mode))
	{
		ms_puterror_is_dir(words[0]);
		exit(126);
	}
	words[0] = add_path;
}

static char	**ms_get_paths(char **envp)
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
				return (NULL);
			paths = ft_split(path, ':');
			free(path);
			if (!paths)
				return (NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

static char	*ms_change_to_absolute(char **paths, char **cmd_word)
{
	char	*path;
	char	*tmp;
	int		i;

	i = -1;
	while (paths && paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
		{
			ms_puterror_cmd(NULL, "malloc");
			exit(127);
		}
		tmp = ft_strjoin(path, *cmd_word);
		free(path);
		if (!tmp)
		{
			ms_puterror_cmd(NULL, "malloc");
			exit(127);
		}
		if (access(tmp, F_OK & X_OK) == 0)
			return (tmp);
		free(tmp);
	}
	return (NULL);
}

static t_bool	ms_is_dir(struct stat buf, char **words)
{
	if (words[0][0] == '/' && access(words[0], F_OK & X_OK) == 0)
	{
		if (stat(words[0], &buf) == 0 && S_ISDIR(buf.st_mode))
		{
			ms_puterror_is_dir(words[0]);
			exit(126);
		}
		return (TRUE);
	}
	return (FALSE);
}
