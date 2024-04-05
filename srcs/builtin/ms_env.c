/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:34:39 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/05 21:06:34 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_builtin.h"
#include "ms_env.h"
#include "ms_error.h"
#include <unistd.h>

static int		ms_env_exec(char **argv, char **envp);
static char		**ms_env_convert(t_env **new_env, char **argv, t_env **env);

int	ms_env(int argc, char **argv, t_env **env)
{
	t_env	**new_env;
	char	**envp;

	(void)argc;
	new_env = (t_env **)malloc(sizeof(t_env *));
	if (!new_env)
		return (EXIT_FAILURE);
	*new_env = NULL;
	argv = ms_env_convert(new_env, argv + 1, env);
	if (!argv)
	{
		free(new_env);
		return (EXIT_FAILURE);
	}
	envp = ms_env_serialize_union(env, new_env);
	if (!envp)
	{
		ms_puterror_cmd(*env, "env");
		ms_env_clear(new_env);
		free(new_env);
		return (EXIT_FAILURE);
	}
	ms_env_clear(new_env);
	free(new_env);
	return (ms_env_exec(argv, envp));
}

static char	**ms_env_convert(t_env **new_env, char **argv, t_env **env)
{
	t_env	*node;

	while (*argv)
	{
		if (ft_strchr(*argv, '=') == NULL)
			break ;
		else
		{
			node = ms_str_to_env(*argv);
			if (!node)
			{
				ms_puterror_cmd(*env, "env");
				ms_env_clear(new_env);
				return (NULL);
			}
			ms_env_push_back(new_env, node);
		}
		argv++;
	}
	return (argv);
}

static int	ms_env_exec(char **argv, char **envp)
{
	int	status;
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	status = execve(*argv, argv, envp);
	if (status == -1)
	{
		ms_puterror_cmd(NULL, *argv);
		exit_code = EXIT_FAILURE;
	}
	while (*envp)
		free(*envp++);
	free(envp);
	return (exit_code);
}
