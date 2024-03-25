/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:48:15 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/25 19:49:57 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ms_env.h"
#include <unistd.h>
#include <stdio.h>

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
			printf ("envp[i] : %s\n", envp[i]);
			path = ft_strdup(envp[i] + 5);
			if (!path)
				return (NULL);
			paths = ft_split(path, ':');
			free(path);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

t_bool	ms_is_builtin(char *word)
{
	if (ft_strcmp(word, "echo") == 0)
		return (TRUE);
	if (ft_strcmp(word, "cd") == 0)
		return (TRUE);
	if (ft_strcmp(word, "pwd") == 0)
		return (TRUE);
	if (ft_strcmp(word, "export") == 0)
		return (TRUE);
	if (ft_strcmp(word, "unset") == 0)
		return (TRUE);
	if (ft_strcmp(word, "env") == 0)
		return (TRUE);
	if (ft_strcmp(word, "exit") == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	ms_add_path(char **paths, char *cmd_word)
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
		tmp = ft_strjoin(path, cmd_word);
		free(path);
		if (!tmp)
			return (FALSE);
		if (access(tmp, F_OK & X_OK) == 0)
		{
			free(cmd_word);
			cmd_word = tmp;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	ms_find_path(char *cmd_word, t_env *env)
{
	char	*path;
	char	**paths;
	char	**envp;

	envp = ms_env_serialize(env);
	if (!cmd_word)
		return ;
	if (!envp)
		return ;
	paths = ms_get_paths(envp);
	if (!paths)
	{
		ms_env_clear(env);
		ms_clear_sec_dimentional(words);
		ms_clear_sec_dimentional(envp);
		return ;
	}
	ms_add_path(paths, cmd_word);
}