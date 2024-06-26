/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:49:17 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:28:45 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtin_bonus.h"
#include "ms_env_bonus.h"
#include "ms_error_bonus.h"

static void	ms_export_env(t_env **env, char *str);

int	ms_export(int argc, char **argv, t_env **env)
{
	if (argc == 1)
		ms_env_print_all(*env);
	else
	{
		while (*(++argv))
			ms_export_env(env, *argv);
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
