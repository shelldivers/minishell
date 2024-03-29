/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:09:43 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/29 20:25:52 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "ft_bool.h"
# include "ms_parser.h"
# include "ms_env.h"

typedef struct s_exec
{
	char	**words;
	int		words_size;
	int		origin_fd[2];
	int		fd[2];
	int		pipe[2][2];
	int		pipe_idx;
	int		pipe_cnt;
	int		exit_code;
	int		cmd_cnt;
}				t_exec;

/*================ exec ==================*/
void	ms_exec(t_ast *ast, t_env **env);
void	ms_exec_in_order(t_ast *ast, t_exec *exec_info, t_env **env);
void	wait_child_process(t_exec *exec_info);
t_exec	*ms_new_exec_info(t_env **env);
/*================ op ==================*/
t_bool	ms_exec_based_on_op(t_ast *ast, t_exec *exec_info, t_env **env);
// t_bool	ms_exec_subshell(t_ast *ast, t_exec *exec_info, t_env **env);
void	ms_exec_io_file(t_ast *ast, t_exec *exec_info, t_env **env);
void	ms_exec_io_file_write(t_exec *exec_info, const char *filename);
void	ms_exec_io_file_append(t_exec *exec_info, const char *filename);
void	ms_exec_io_file_read(t_exec *exec_info, const char *filename);
t_bool	ms_create_words(t_exec *exec_info, char *word);
t_bool	ms_add_word(t_exec *exec_info, char *word);
size_t	ms_words_size(char **words);
void	ms_clear_sec_dimentional(char **words);
/*================ commands ==================*/
t_bool	ms_exec_is_builtin(t_exec *exec_info);
void	ms_exec_non_builtin(t_exec *exec_info, t_env **env);
void	ms_exec_words(t_exec *exec_info, t_env **env);
void	ms_exec_builtin(t_exec *exec_info, t_env **env);
void	ms_exec_builtin2(t_exec *exec_info, t_env **env);
/*================ pipe, fd ==================*/
t_bool	ms_reset_fd(t_exec *exec_info);
t_bool	ms_close_parent_pipe(t_exec *exec_info);
t_bool	ms_dup_based_on_pipe_idx(t_exec *exec_info);
t_bool	ms_exec_pipe(t_ast *ast, t_exec *exec_info, t_env **env);
/*================ path ==================*/
t_bool	ms_add_path(t_exec *exec_info, t_env **env);
t_bool	**ms_get_paths(char **envp);
t_bool	ms_change_to_absolute(char **paths, char **cmd_word);

#endif