/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:09:43 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/22 16:35:45 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ms_parser.h"
# include "ft_bool.h"

typedef struct s_execz
{
	char	**words;
	int		words_size;
	int		fd[2];
	int		pipe[2][2];
	int		pipe_cnt;
}				t_exec;

void	ms_exec(t_ast *ast, int *exit_code);
/*================exec_unit==================*/
t_bool	ms_exec_if(t_exec *exec_info);
t_bool	ms_exec_pipe(t_exec *exec_info, int *exit_code);
t_bool	ms_exec_subshell(t_ast *ast, int *exit_code);
t_bool	ms_exec_io_file(enum e_type type, char *filename, t_exec *exec_info);
t_bool	ms_exec_io_here(t_ast *ast, t_exec *exec_info);
t_bool	ms_exec_cmd_word(char *word, t_exec *exec_info);
t_bool	ms_exec_word(char *word, t_exec *exec_info);
/*================words==================*/
char	**ms_create_words(char *word);
char	**ms_add_word(char **words, size_t size, char *word);
void	ms_clear_words(char **words);

#endif