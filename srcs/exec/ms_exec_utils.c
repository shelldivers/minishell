/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:25:35 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/02 19:52:24 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ms_error.h"
#include "ms_env.h"
#include "ms_exec.h"

void	ms_wait_child_process(t_exec *exec_info)
{
	int	status;

	while (exec_info->cmd_cnt)
	{
		waitpid(-1, &status, 0);
		exec_info->exit_code = WEXITSTATUS(status);
		exec_info->cmd_cnt--;
	}
}

t_exec	*ms_new_exec_info(t_env **env)
{
	t_exec	*exec_info;

	exec_info = (t_exec *)malloc(sizeof(t_exec));
	if (!exec_info)
	{
		ms_puterror_cmd(*env, "malloc");
		return (NULL);
	}
	ms_init_exec_info(exec_info);
	return (exec_info);
}

void	reset_exec_info(t_exec *exec_info)
{
	ms_clear_all_fd(exec_info);
	reset_io(exec_info);
	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
	free (exec_info->words);
	exec_info->words = NULL;
	free (exec_info);
	exec_info = NULL;
}
