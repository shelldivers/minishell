/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:48:15 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/02 19:52:53 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ms_error.h"
#include "ms_env.h"
#include "ms_exec.h"

static char		**ms_get_paths(char **envp);
static t_bool	ms_change_to_absolute(char **paths, char **cmd_word);

t_bool	ms_add_path(t_exec *exec_info, t_env **env)
{
	char	**words;
	char	**envp;
	char	**paths;

	words = exec_info->words;
	if (words[0][0] == '/' && access(words[0], F_OK & X_OK) == 0)
		return (TRUE);
	envp = ms_env_serialize(*env);
	paths = ms_get_paths(envp);
	if (!ms_change_to_absolute(paths, &words[0]))
	{
		ms_clear_sec_dimentional(envp);
		ms_clear_sec_dimentional(paths);
		return (FALSE);
	}
	ms_clear_sec_dimentional(envp);
	ms_clear_sec_dimentional(paths);
	return (TRUE);
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

static t_bool	ms_change_to_absolute(char **paths, char **cmd_word)
{
	char	*path;
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (FALSE);
		tmp = ft_strjoin(path, *cmd_word);
		free(path);
		if (!tmp)
			return (FALSE);
		if (access(tmp, F_OK & X_OK) == 0)
		{
			*cmd_word = tmp;
			return (TRUE);
		}
		free(tmp);
		i++;
	}
	return (FALSE);
}
