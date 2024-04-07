/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:09:43 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/07 21:36:04 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXEC_H
# define MS_EXEC_H
# define SHELLNAME "/tmp/.SHELLDIVERS_"
# define HEREDOC "minidoc> "
# define MAX_HEREDOC 7
# include "ft_bool.h"
# include "ms_parser.h"
# include "ms_env.h"
# include <stdlib.h>

typedef struct s_exec
{
	char		**words;
	int			words_size;
	int			origin_fd[2];
	int			fd[2];
	int			pipe[2][2];
	int			pipe_idx;
	int			cmd_cnt;
	int			execed_cmd_cnt;
	int			heredoc_fd[7];
	int			heredoc_seq;
	pid_t		pid;
}				t_exec;

/*================ exec ==================*/
void		ms_exec(t_ast *ast, t_env **env);
void		ms_after_exec(t_exec *exec_info);
t_bool		ms_exec_in_order(t_ast *ast, t_exec *exec_info, t_env **env);
int			ms_exec_based_on_op(t_ast *ast, t_exec *exec_info, t_env **env);

/*================ utils ==================*/
void		ms_get_line_with_fd(const char *type, char *end, int fd);
void		ms_wait_child_process(t_exec *exec_info);
t_exec		*ms_new_exec_info(t_env **env);
size_t		ms_max_heredoc(t_token **token);
void		ms_set_exited(int status);

void		dup2_fd(t_exec *exec_info);

int			wifexit(int x);
int			wexitstatus(int x);
int			wifsignaled(int x);
int			wstatus(int x);

/*================ init & clear ==================*/
void		ms_init_exec_info(t_exec *exec_info);
void		ms_clear_sec_dimentional(char **words);
void		ms_reset_exec_info(t_exec *exec_info);
void		ms_reset_io(t_exec *exec_info);

/*================ redirect ==================*/
t_bool		ms_exec_io_file(t_ast *ast, t_exec *exec_info, t_env **env);
t_bool		ms_exec_io_file_write(t_exec *exec_info, char *filename);
t_bool		ms_exec_io_file_append(t_exec *exec_info, char *filename);
t_bool		ms_exec_io_file_read(t_exec *exec_info, char *filename);
char		*check_ambiguous_redirect(t_env **env, char *filename);

/*================ heredoc ==================*/
t_bool		ms_exec_io_here(t_exec *exec_info);

t_bool		ms_exec_heredoc_before(t_ast *ast);
t_bool		ms_here_doc_in_order(t_ast *ast, int seq);
t_bool		ms_set_heredoc(t_ast *ast, const int seq);
char		*ms_get_heredoc_filename(int idx);
void		ms_clear_heredoc(t_exec *exec_info);
char		*ms_quote_removal_dup(char *word, size_t i, size_t j);

/*================ commands ==================*/
t_bool		ms_exec_is_builtin(t_exec *exec_info, t_env **env, char **words);
void		ms_exec_non_builtin(t_exec *exec_info, t_env **env, char **words);
void		ms_exec_words(t_exec *exec_info, t_env **env);
t_bool		ms_exec_builtin(t_exec *exec_info, t_env **env, \
char **words, int (f)(int, char **, t_env **));
t_bool		ms_add_word(t_exec *exec_info, char *word);
int			ms_words_size(char **words);

void		ms_exec_commands_fork(t_exec *exec_info, t_env **env, char **words);
void		ms_exec_is_builtin_fork(t_env **env, char **words);
void		ms_exec_builtin_fork(t_env **env, \
char **words, int (f)(int, char **, t_env **));
/*================ pipe ==================*/
t_bool		ms_exec_pipe(t_exec *exec_info);
void		ms_dup_pipe(t_exec *exec_info);
void		ms_close_pipe(t_exec *exec_info);
void		ms_dup_first_pipe(t_exec *exec_info);
void		ms_dup_middle_pipe(t_exec *exec_info);
void		ms_dup_last_pipe(t_exec *exec_info);
void		ms_close_first_pipe(t_exec *exec_info);
void		ms_close_middle_pipe(t_exec *exec_info);
void		ms_close_last_pipe(t_exec *exec_info);

/*================ fd ==================*/
void		ms_close_all_fd(t_exec *exec_info);
void		ms_close_all_pipe(t_exec *exec_info);
void		ms_close_all_pipe2(t_exec *exec_info);
void		ms_close_stdout(t_exec *exec_info);
void		ms_close_stdin(t_exec *exec_info);

/*================ path ==================*/
void		ms_add_path(char **words, t_env **env);
int			s_isdir(int m);
void		ms_is_dir(char **words);

#endif
