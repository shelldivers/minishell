/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_unit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:10:51 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/25 12:38:48 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "ms_parser.h"
#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>

// t_bool	ms_exec_if(t_exec *exec_info)
// {
// 	if (exec_info->words)
// 	{
// 		execve(exec_info->words[0], exec_info->words, NULL);
// 		ms_clear_words(exec_info->words);
// 	}
// 	return (TRUE);
// }

// t_bool	ms_exec_pipe(t_exec *exec_info, int *exit_code)
// {
// 	int		pid;

// 	pipe(exec_info->pipe[exec_info->pipe_cnt % 2]);
// 	exec_info->pipe_cnt++;
// 	pid = fork();
// 	if (pid == -1)
// 		return (FALSE);
// 	if (pid == 0)
// 	{
// 		if (exec_info->pipe_cnt % 2)
// 		{
// 			dup2(exec_info->pipe[1][0], STDIN_FILENO);
// 			close(exec_info->pipe[1][0]);
// 		}
// 		else
// 		{
// 			dup2(exec_info->pipe[0][1], STDOUT_FILENO);
// 			close(exec_info->pipe[0][1]);
// 		}
// 		if (exec_info->words)
// 		{
// 			execve(exec_info->words[0], exec_info->words, NULL);
// 			ms_clear_words(exec_info->words);
// 		}
// 		exit(0);
// 	}
// 	if (exec_info->pipe_cnt % 2)
// 		close(exec_info->pipe[1][0]);
// 	else
// 		close(exec_info->pipe[0][1]);
// 	*exit_code = waitpid(pid, NULL, 0);
// 	return (TRUE);
// }

// t_bool	ms_exec_subshell(t_ast *ast, int *exit_code)
// {
// 	int		pid;
// 	t_ast	*sub_ast;

// 	sub_ast = NULL;
// 	pid = fork();
// 	if (pid == -1)
// 		return (FALSE);
// 	if (pid == 0)
// 	{
// 		ms_parser(&sub_ast, ast->token + 1, ast->token_size - 2);
// 		ms_exec(sub_ast, exit_code);
// 		ms_clear_ast(sub_ast);
// 		exit(0);
// 	}
// 	*exit_code = waitpid(pid, NULL, 0);
// 	return (TRUE);
// }

// t_bool	ms_exec_io_file(enum e_type type, char *filename, t_exec *exec_info)
// {
// 	if (type == TDREAD)
// 	{
// 		if (exec_info->fd[0])
// 		{
// 			close(exec_info->fd[0]);
// 			exec_info->fd[0] = 0;
// 		}
// 		exec_info->fd[0] = open(filename, O_RDONLY);
// 	}
// 	else
// 	{
// 		if (exec_info->fd[1])
// 		{
// 			close(exec_info->fd[1]);
// 			exec_info->fd[1] = 0;
// 		}
// 		if (type == TDGREAT)
// 			exec_info->fd[1] = open(\
// 			filename, O_RDWR | O_CREAT | O_APPEND, 0644);
// 		else if (type == TDWRITE)
// 			exec_info->fd[1] = open(filename, O_RDWR | O_CREAT, 0644);
// 	}
// 	return (TRUE);
// }

// t_bool	ms_exec_io_here(t_ast *ast, t_exec *exec_info)
// {
// 	char	*line;

// 	line = NULL;
// 	exec_info->fd[0] = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (exec_info->fd[0] == -1)
// 		return (FALSE);
// 	while (1)
// 	{
// 		line = readline("heredoc> ");
// 		if (!line || !ft_strcmp(line, ast->right->token[0]->value))
// 			break ;
// 		write(exec_info->fd[0], line, ft_strlen(line));
// 		write(exec_info->fd[0], "\n", 1);
// 		free(line);
// 	}
// 	return (TRUE);
// }

// t_bool	ms_exec_cmd_word(char *word, t_exec *exec_info)
// {
// 	exec_info->words = ms_create_words(word);
// 	if (!exec_info->words)
// 		return (FALSE);
// 	exec_info->words_size = 1;
// 	return (TRUE);
// }

// t_bool	ms_exec_word(char *word, t_exec *exec_info)
// {
// 	exec_info->words = ms_add_word(\
// 	exec_info->words, exec_info->words_size, word);
// 	if (!exec_info->words)
// 		return (FALSE);
// 	exec_info->words_size++;
// 	return (TRUE);
// }
