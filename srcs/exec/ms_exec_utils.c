/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:25:35 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/04 11:29:44 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ms_error.h"
#include "ms_exec.h"
#include <readline/readline.h>

void	get_line_with_fd(const char *type, char *end, int fd)
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

void	ms_max_heredoc(t_ast *ast)
{
	size_t	i;

	i = 0;
	if (!ast)
		return ;
	if (ast->op == OPIO_HERE)
		i++;
	if (ast->left)
		ms_max_heredoc(ast->left);
	if (ast->right)
		ms_max_heredoc(ast->right);
	if (i > 7)
	{
		write(2, "maximum here-document count exceeded\n", 36);
		exit(2);
	}
}

void	ms_wait_child_process(t_exec *exec_info)
{
	int		status;

	while (exec_info->execed_cmd_cnt)
	{
		waitpid(-1, &status, 0);
		exec_info->exit_code = WEXITSTATUS(status);
		exec_info->execed_cmd_cnt--;
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

void	ms_reset_exec_info(t_exec *exec_info)
{
	if (exec_info->words)
		free (exec_info->words);
	exec_info->words = NULL;
	exec_info->words_size = 0;
}