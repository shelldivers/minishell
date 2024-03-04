/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:49:17 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/04 20:49:18 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtin.h"
#include "ms_env.h"
#include "ms_error.h"
#include <unistd.h>

static void	ms_export_env(t_env **env, char *str);

int	ms_export(int argc, char **argv, t_env **env)
{
	if (argc < 1 || argv == NULL || env == NULL)
		return (EXIT_FAILURE);	// error message
	if (argc == 1 || argv[1] == NULL)
	{
		ms_env_print_all(*env);
		return (EXIT_SUCCESS);
	}
	argv++;
	while (*argv)
	{
		ms_export_env(env, *argv);
		argv++;
	}
	return (EXIT_SUCCESS);
}

static void	ms_export_env(t_env **env, char *str)
{
	t_env	*node;

	node = ms_str_to_env(str);
	if (!node)
	{
		ms_puterror_cmd(*env, "export");
		return ;
	}
	if (ms_is_valid_env_key(node->key) == FALSE)
		ms_puterror_identifier(*env, "export", node->key);
	else
	{
		if (!ms_setenv(env, node->key, node->value))
			ms_puterror_cmd_arg(*env, "export", node->key);
	}
	free(node->key);
	free(node->value);
	free(node);
}
