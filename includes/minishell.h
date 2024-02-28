/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:24:17 by jiwojung          #+#    #+#             */
/*   Updated: 2024/02/28 17:10:01 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # ifdef __cplusplus
// extern "C" {
// # endif

# include <stdlib.h>

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
	SUBSHELL
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

typedef struct s_parser
{
	t_token			*token;
	struct s_parser	*left;
	struct s_parser	*right;
	enum e_type		operator;
}				t_parser;

/*================seperate_line.c================*/
void	lexer(t_syntax *syntax);
/*================init_clear_line.c================*/
void	init_syntax(t_syntax *syntax);
void	clear_syntax(t_syntax *syntax);
/*================tokenize.c================*/
t_token	**tokenize(t_syntax *syntax);
void	clear_token(t_token **token);
// # ifdef __cplusplus
// }
// # endif


#endif