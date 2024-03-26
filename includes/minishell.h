/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:09:43 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/26 15:17:05 by jiwojung         ###   ########.fr       */
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


/*================exec_unit==================*/
/*================words==================*/


#endif