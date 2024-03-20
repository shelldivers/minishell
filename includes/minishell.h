/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:24:17 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/20 16:12:10 by jiwojung         ###   ########.fr       */
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
	OPCMD_NAME,
	OPIO_HERE,
	OPIO_FILE,
	OPWORD,
	OPNONE
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
	TLPAREN,
	TRPAREN,
	TNONE
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
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_token	**token;
	size_t			token_size;
}				t_ast;

/*================lex.c================*/
void	ms_lexer(t_syntax *syntax);
size_t	ms_count_word(const char *line, const char **op);
size_t	ms_get_op(const char *s1, const char **op);
size_t	ms_get_word(const char *line, const char **op);
size_t	ms_close_quote(const char *line, const char quote);
char	*ms_extract_token(char *line, size_t *start, const char **op);
char	*ms_extract_word(char *line, size_t *start, const char **op);
/*================init.c================*/
void	ms_init_syntax(t_syntax *syntax);
/*================clear.c================*/
void	ms_clear_syntax(t_syntax *syntax);
void	ms_clear_ast(t_ast *ast);
void	ms_clear_token(t_token **token);
/*================tokenize.c================*/
t_token	**ms_tokenizer(t_syntax *syntax);
/*================unterminal.c================*/
size_t	ms_is_and_or(t_ast *ast, t_token **token);
size_t	ms_is_pipeline(t_ast *ast, t_token **token);
size_t	ms_is_command(t_ast *ast, t_token **token);
size_t	ms_is_subshell(t_ast *ast, t_token **token);
size_t	ms_is_simple_command(t_ast *ast, t_token **token);
size_t	ms_is_cmd_suffix(t_ast *ast, t_token **token);
size_t	ms_is_cmd_prefix(t_ast *ast, t_token **token);
size_t	ms_is_io_redirect(t_ast *ast, t_token **token);
size_t	ms_get_op_pos(t_token **token, enum e_type op1, enum e_type op2);
/*================terminal.c================*/
size_t	ms_is_io_file(t_ast *ast, t_token **token);
size_t	ms_is_io_here(t_ast *ast, t_token **token);
size_t	ms_is_word(t_ast *ast, t_token **token);
size_t	ms_is_cmd_word(t_ast *ast, t_token **token);
size_t	ms_is_cmd_name(t_ast *ast, t_token **token);
size_t	ms_is_here_end(t_ast *ast, t_token **token);
size_t	ms_is_filename(t_ast *ast, t_token **token);
/*================ast.c================*/
t_ast	*ms_new_ast(t_token **token, size_t size);
size_t	ms_add_ast(t_ast *ast, t_token **token, \
size_t(f)(t_ast *, t_token **), size_t size, enum e_lr lr);
t_token	**ms_tokenndup(t_token **src, size_t size);
size_t	ms_tokenlen(t_token **token);

#endif