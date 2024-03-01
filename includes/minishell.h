/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:24:17 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/01 16:51:28 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

enum e_grammar
{
	GNONE,
	GCOMPLETE_COMMAND,
	GPIPELINE,
	GSUBSHELL,
	GSIMPLE_COMMAND,
	GCMD_NAME,
	GCMD_WORD,
	GCMD_PREFIX,
	GCMD_SUFFIX,
	GIO_REDIRECT,
	GIO_FILE,
	GIO_HERE,
	GWORD
};

enum e_type
{
	TPIPE,
	TWORD,
	TASSIGNMENT_WORD,
	TAND_IF,
	TOR_IF,
	TDLESS,
	TDGREAT,
	TDREAD,
	TDWRITE,
	TSUBSHELL
};

typedef struct s_syntax
{
	char	*line;
	char	**words;
	size_t	words_cnt;
}				t_syntax;

typedef struct s_token
{
	enum e_type	type;
	char		*value;
}				t_token;

typedef struct s_parse
{
	enum e_grammar	grammar;
	struct s_parser	*left;
	struct s_parser	*right;
	struct s_token	*token;
	size_t			token_size;
}				t_parse;

/*================seperate_line.c================*/
void	lexer(t_syntax *syntax);
/*================init_clear_line.c================*/
void	init_syntax(t_syntax *syntax);
void	init_parse(t_parse **parse_head, t_token **token, size_t size);
void	clear_syntax(t_syntax *syntax);
void	clear_parse_tree(t_parse *parse_head);
void	clear_token(t_token **token);
/*================tokenize.c================*/
t_token	**tokenize(t_syntax *syntax);
void	clear_token(t_token **token);
#endif