/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:48:15 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/07 21:38:10 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_error.h"
#include "ms_exec.h"
#include <sys/stat.h>
#include <unistd.h>

static char		**ms_get_paths(char **envp);
static char		*ms_change_to_absolute(char **paths, char **cmd_word);
static void		check_path_words(char **words, char **paths);

void	ms_add_path(char **words, t_env **env)
{
	char		*add_path;
	char		**envp;
	char		**paths;
	struct stat	buf;

	stat(words[0], &buf);
	ms_is_dir(words);
	envp = ms_env_serialize(*env);
	paths = ms_get_paths(envp);
	check_path_words(words, paths);
	add_path = ms_change_to_absolute(paths, words);
	if (!add_path)
		add_path = ft_strdup(words[0]);
	ms_clear_sec_dimentional(envp);
	ms_clear_sec_dimentional(paths);
	if (stat(add_path, &buf) == 0 && s_isdir(buf.st_mode))
	{
		ms_puterror_is_dir(words[0]);
		exit(126);
	}
	words[0] = add_path;
}

static void	check_path_words(char **words, char **paths)
{
	if (ft_strlen(words[0]) == 0)
	{
		ms_puterror_no_command(words[0]);
		exit(127);
	}
	if (!paths || !paths[0])
	{
		ms_puterror_no_file(words[0]);
		exit(127);
	}
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
			ms_puterror_cmd(NULL, "malloc");
		tmp = ft_strjoin(path, *cmd_word);
		free(path);
		if (!tmp)
			ms_puterror_cmd(NULL, "malloc");
		if (access(tmp, F_OK & X_OK) == 0)
			return (tmp);
		free(tmp);
	}
	return (NULL);
}
