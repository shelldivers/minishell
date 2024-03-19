/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:24:17 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/19 18:43:11 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// # include "ft_bool.h"
// # include "ms_env.h"

# include <stdlib.h>

enum e_lr
{
	LEFT,
	RIGHT
};

enum e_grammar
{
	GAND_OR,
	GPIPELINE,
	GCOMMAND,
	GSUBSHELL,
	GSIMPLE_COMMAND,
	GCMD_WORD,
	GCMD_SUFFIX,
	GCMD_PREFIX,
	GIO_REDIRECT,
	GIO_FILE,
	GIO_HERE,
	GWORD,
	GIO_NUMBER,
	GFILENAME,
	GHERE_END,
	GCMD_NAME,
	GNONE
};

enum e_op
{
	OPPIPE,
	OPAND_IF,
	OPOR_IF,
	OPSUBSHELL,
	OPDREAD,
	OPDWRITE,
	OPDGREAT,
	OPDLESS,
	OPCMD_WORD,
	OPNONE
};

enum e_type
{
	TPIPE,
	TWORD,
	TIO_NUMBER,
	TAND_IF,
	TOR_IF,
	TDLESS,
	TDGREAT,
	TDREAD,
	TDWRITE,
	TLPAREN,
	TRPAREN
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

typedef struct s_ast
{
	enum e_op		op;
	enum e_grammar	grammar;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_token	**token;
	size_t			token_size;
	char			**words;
}				t_ast;

/*================lex.c================*/
void	lexer(t_syntax *syntax);
/*================init.c================*/
void	init_syntax(t_syntax *syntax);
/*================clear.c================*/
void	clear_syntax(t_syntax *syntax);
void	clear_ast(t_ast *ast);
void	clear_token(t_token **token);
void	clear_all(t_syntax *syntax, t_token **token, t_ast *ast);
/*================tokenize.c================*/
t_token	**tokenize(t_syntax *syntax);
/*================unterminal.c================*/
size_t	isand_or(t_ast *ast, t_token **token);
size_t	ispipeline(t_ast *ast, t_token **token);
size_t	iscommand(t_ast *ast, t_token **token);
size_t	issubshell(t_ast *ast, t_token **token);
size_t	issimple_command(t_ast *ast, t_token **token);
size_t	iscmd_suffix(t_ast *ast, t_token **token);
size_t	iscmd_prefix(t_ast *ast, t_token **token);
size_t	isio_redirect(t_ast *ast, t_token **token);
/*================terminal.c================*/
size_t	isio_file(t_ast *ast, t_token **token);
size_t	isio_here(t_ast *ast, t_token **token);
size_t	isword(t_ast *ast, t_token **token);
size_t	isio_number(t_ast *ast, t_token **token);
size_t	iscmd_word(t_ast *ast, t_token **token);
size_t	iscmd_name(t_ast *ast, t_token **token);
size_t	ishere_end(t_ast *ast, t_token **token);
size_t	isfilename(t_ast *ast, t_token **token);
/*================ast.c================*/
t_ast	*new_ast(t_token **token, size_t size);
size_t	add_ast(t_ast *ast, t_token **token, \
size_t(f)(t_ast *, t_token **), size_t size, enum e_lr lr);
t_token	**tokenndup(t_token **src, size_t size);
size_t	tokenlen(t_token **token);

#endif