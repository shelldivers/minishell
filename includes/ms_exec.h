/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:09:43 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/02 19:49:08 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXEC_H
# define MS_EXEC_H

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
t_bool	ms_exec_in_order(t_ast *ast, t_exec *exec_info, t_env **env);
int		ms_exec_based_on_op(t_ast *ast, t_exec *exec_info, t_env **env);

/*================ utils ==================*/
void	ms_wait_child_process(t_exec *exec_info);
t_exec	*ms_new_exec_info(t_env **env);
void	reset_exec_info(t_exec *exec_info);

/*================ init & clear ==================*/
void	ms_init_exec_info(t_exec *exec_info);
void	ms_clear_sec_dimentional(char **words);

/*================ redirect ==================*/
t_bool	ms_exec_io_file(t_ast *ast, t_exec *exec_info);
t_bool	ms_exec_io_file_write(t_exec *exec_info, const char *filename);
t_bool	ms_exec_io_file_append(t_exec *exec_info, const char *filename);
t_bool	ms_exec_io_file_read(t_exec *exec_info, const char *filename);

/*================ heredoc ==================*/
t_bool	ms_exec_io_here(t_exec *exec_info, const char *here_end);

/*================ commands ==================*/
t_bool	ms_exec_is_builtin(t_exec *exec_info);
void	ms_exec_non_builtin(t_exec *exec_info, t_env **env);
void	ms_exec_words(t_exec *exec_info, t_env **env);
void	ms_exec_builtin(t_exec *exec_info, t_env **env);
void	ms_exec_builtin2(t_exec *exec_info, t_env **env);

t_bool	ms_add_word(t_exec *exec_info, char *word);

/*================ pipe ==================*/
t_bool	ms_exec_pipe(t_ast *ast, t_exec *exec_info, t_env **env);
t_bool	ms_dup_based_on_pipe_idx(t_exec *exec_info);
t_bool	ms_close_parent_pipe(t_exec *exec_info);

/*================ fd ==================*/
t_bool	ms_close_all_fd(t_exec *exec_info);
void	reset_io(t_exec *exec_info);

/*================ path ==================*/
t_bool	ms_add_path(t_exec *exec_info, t_env **env);

#endif