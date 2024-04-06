/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_io_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:08:04 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/06 20:37:18 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_error.h"
#include "ms_exec.h"
#include "ms_expand.h"
#include "ms_signal.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

t_bool	ms_exec_io_file(t_ast *ast, t_exec *exec_info, t_env **env)
{
	const char	*redirect = ast->token[0]->value;
	char		*filename;
	t_bool		ret;

	filename = ast->token[1]->value;
	filename = check_ambiguous_redirect(env, filename);
	if (!filename)
		return (FALSE);
	ret = TRUE;
	if (ft_strcmp(redirect, ">") == 0)
		ret = ms_exec_io_file_write(exec_info, filename);
	else if (ft_strcmp(redirect, ">>") == 0)
		ret = ms_exec_io_file_append(exec_info, filename);
	else if (ft_strcmp(redirect, "<") == 0)
		ret = ms_exec_io_file_read(exec_info, filename);
	free(filename);
	return (ret);
}

// error handling in this function
t_bool	ms_exec_io_file_write(t_exec *exec_info, char *filename)
{
	if (exec_info->fd[1] != -1)
	{
		close(exec_info->fd[1]);
		exec_info->fd[1] = -1;
	}
	exec_info->fd[1] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec_info->fd[1] == -1)
	{
		ms_puterror_cmd(NULL, filename);
		return (FALSE);
	}
	return (TRUE);
}

// error handling in this function
t_bool	ms_exec_io_file_append(t_exec *exec_info, char *filename)
{
	if (exec_info->fd[1] != -1)
	{
		close(exec_info->fd[1]);
		exec_info->fd[1] = -1;
	}
	exec_info->fd[1] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (exec_info->fd[1] == -1)
	{
		ms_puterror_cmd(NULL, filename);
		return (FALSE);
	}
	return (TRUE);
}

// error handling in this function
t_bool	ms_exec_io_file_read(t_exec *exec_info, char *filename)
{
	if (exec_info->fd[0] != -1)
	{
		close(exec_info->fd[0]);
		exec_info->fd[0] = -1;
	}
	exec_info->fd[0] = open(filename, O_RDONLY);
	if (exec_info->fd[0] == -1)
	{
		ms_puterror_cmd(NULL, filename);
		return (FALSE);
	}
	return (TRUE);
}

char	*check_ambiguous_redirect(t_env **env, char *filename)
{
	char	**words;
	char	**expanded_word;

	words = (char **)malloc(sizeof(char *) * 2);
	if (!words)
	{
		ms_puterror_cmd(NULL, "malloc");
		return (NULL);
	}
	words[0] = filename;
	words[1] = NULL;
	expanded_word = ms_expansion(words, *env);
	if (!expanded_word[0] || expanded_word[1])
	{
		ms_puterror_ambiguous_redirect(filename);
		ms_clear_sec_dimentional(expanded_word);
		return (FALSE);
	}
	free(words);
	free(expanded_word);
	return (expanded_word[0]);
}
