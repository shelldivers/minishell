/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:34:39 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:28:30 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env_bonus.h"
#include "ft_printf.h"
#include "libft.h"
#include "ms_builtin_bonus.h"
#include "ms_exec_bonus.h"
#include "ms_error_bonus.h"
#include <unistd.h>

static char	*ms_join_argv(char **argv);
static char	**ms_append_envp(char **argv, t_env **env, char ***envp);
static void	assign_envp(char *const *argv, char **new_envp, int size);
static int	ms_env_print(char *line, char **envp);

int	ms_env(int argc, char **argv, t_env **env)
{
	char	*line;
	char	**envp;
	int		result;

	(void)argc;
	argv = ms_append_envp(++argv, env, &envp);
	if (!argv)
	{
		ms_puterror_cmd(*env, "env");
		return (EXIT_FAILURE);
	}
	line = ms_join_argv(argv);
	if (!line)
	{
		ms_puterror_cmd(*env, "env");
		return (EXIT_FAILURE);
	}
	if (*line == '\0')
		result = ms_env_print(line, envp);
	else
		result = ms_env_exec(line, envp);
	ms_clear_sec_dimentional(envp);
	return (result);
}

static char	*ms_join_argv(char **argv)
{
	char	*line;
	int		i;
	size_t	count;
	size_t	len;

	i = 0;
	count = 0;
	while (argv[i])
		count += ft_strlen(argv[i++]) + 1;
	line = (char *)malloc(sizeof(char) * count);
	if (!line)
		return (NULL);
	i = 0;
	count = 0;
	while (argv[i])
	{
		len = ft_strlen(argv[i]);
		ft_memcpy(line + count, argv[i], len);
		count += len;
		if (argv[i + 1] != NULL)
			line[count++] = ' ';
		i++;
	}
	line[count] = '\0';
	return (line);
}

static char	**ms_append_envp(char **argv, t_env **env, char ***envp)
{
	char	**new_envp;
	int		size;
	t_env	**tmp;

	size = 0;
	while (argv[size] && ft_strchr(argv[size], '=') != NULL)
		size++;
	new_envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_envp)
		return (NULL);
	new_envp[size] = NULL;
	assign_envp(argv, new_envp, size);
	tmp = ms_env_deserialize(new_envp);
	if (!tmp)
		return (NULL);
	free(new_envp);
	*envp = ms_env_serialize_union(env, tmp);
	ms_env_clear(tmp);
	free(tmp);
	return (&argv[size]);
}

static void	assign_envp(char *const *argv, char **new_envp, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		new_envp[i] = argv[i];
		i++;
	}
}

static int	ms_env_print(char *line, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		ft_printf("%s\n", envp[i++]);
	free(line);
	return (EXIT_SUCCESS);
}
