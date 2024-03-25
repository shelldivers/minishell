/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:09:43 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/25 12:39:07 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "ft_bool.h"
# include "ms_parser.h"

typedef struct s_exec
{
	char	**words;
	int		words_size;
	int		fd[2];
	int		pipe[2][2];
	int		pipe_cnt;
	int		exit_code;
}				t_exec;

void	ms_exec(t_ast *ast, char **envp);
/*================exec_unit==================*/
/*================words==================*/
char	**ms_create_words(char *word);
char	**ms_add_word(char **words, size_t size, char *word);
void	ms_clear_sec_dimentional(char **words);

#endif