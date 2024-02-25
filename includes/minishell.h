/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:24:17 by jiwojung          #+#    #+#             */
/*   Updated: 2024/02/25 18:54:46 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # ifdef __cplusplus
// extern "C" {
// # endif

typedef struct s_syntax
{
	char	*line;
	char	**word_list;
}				t_syntax;

/*================seperate_line.c================*/
void	separate_words(t_syntax *syntax);

// # ifdef __cplusplus
// }
// # endif


#endif