/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:25:35 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/06 20:06:43 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "ms_error.h"
#include "ms_exec.h"
#include "ms_signal.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

void	ms_get_line_with_fd(const char *type, char *end, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(type);
		if (!line)
			break ;
		if (end && !ft_strcmp(line, end))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	ms_max_heredoc(t_token **token)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	if (!token || !*token)
		return ;
	while (token[i])
	{
		if (token[i]->type == TDLESS)
			cnt++;
		i++;
	}
	if (cnt > MAX_HEREDOC)
	{
		ms_puterror_max_here_doc();
		g_exit = 2;
		exit(g_exit);
	}
}

void	ms_wait_child_process(t_exec *exec_info)
{
	int		status;

	while (exec_info->execed_cmd_cnt)
	{
		waitpid(-1, &status, 0);
		if (wifexit(status) == TRUE)
			g_exit = wexitstatus(status);
		exec_info->execed_cmd_cnt--;
	}
	ms_print_signaled(status);
	ms_set_signal_prompt();
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
