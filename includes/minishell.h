/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:24:17 by jiwojung          #+#    #+#             */
/*   Updated: 2024/02/26 19:17:08 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # ifdef __cplusplus
// extern "C" {
// # endif

enum e_type
{
	PIPE,
	WORD,
	ASSIGNMENT_WORD,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	DREAD,
	DWRITE,
	LBRACKET,
	RBRACKET
};

typedef struct s_token
{
	enum e_type	type;
	char		*value;
}				t_token;

typedef struct s_syntax
{
	char	*line;
	char	**words;
	size_t	words_cnt;
}				t_syntax;

/*================seperate_line.c================*/
void	separate_words(t_syntax *syntax);

// # ifdef __cplusplus
// }
// # endif


#endif