/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:24:17 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/05 14:07:57 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

enum e_grammar
{
	GNONE,
	GAND_OR,
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
	struct s_parse	*left;
	struct s_parse	*right;
	struct s_token	**token;
	size_t			token_size;
}				t_parse;

/*================seperate_line.c================*/
void	lexer(t_syntax *syntax);
/*================init.c================*/
void	init_syntax(t_syntax *syntax);
void	init_parse(t_parse *parse, t_token **token, size_t size);
/*================clear.c================*/
void	clear_syntax(t_syntax *syntax);
void	clear_parse(t_parse *parse);
void	clear_token(t_token **token);
void	clear_all(t_syntax *syntax, t_token **token, t_parse *parse);
/*================tokenize.c================*/
t_token	**tokenize(t_syntax *syntax);
/*================is_grammar.c================*/
size_t	is_io_here(t_token **token);
size_t	is_io_file(t_token **token);
size_t	is_io_redirect(t_token **token);
size_t	is_redirect_list(t_token **token);
size_t	is_cmd_suffix(t_token **token);
size_t	is_word(t_token **token);
/*================parse_tree.c================*/
t_parse	*new_parse(t_parse *parse, t_token **token, size_t size);
#endif