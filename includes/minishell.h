/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:09:43 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/21 17:22:19 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ms_parser.h"
# include "ft_bool.h"

typedef struct s_exec
{
	char	**words;
	int		words_size;
	int		exit_code;
	int		fd[2];
	int		pipe[2][2];
	int		pipe_cnt;
}				t_exec;

void	ms_exec(t_ast *ast);
/*================exec_unit==================*/
t_bool	ms_exec_if(t_ast *ast, t_exec *exec_info);
t_bool	ms_exec_pipe(t_ast *ast, t_exec *exec_info);
t_bool	ms_exec_subshell(t_ast *ast, t_exec *exec_info);
t_bool	ms_exec_io_file(t_ast *ast, t_exec *exec_info);
t_bool	ms_exec_io_here(t_ast *ast, t_exec *exec_info);
t_bool	ms_exec_cmd_word(t_ast *ast, t_exec *exec_info);
t_bool	ms_exec_word(char *word, t_exec *exec_info);

#endif