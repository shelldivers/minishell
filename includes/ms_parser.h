/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:24:17 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/06 15:21:49 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSER_H
# define MS_PARSER_H
# define OP_SIZE 9
# include "ft_bool.h"
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
	int		words_cnt;
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
	int				token_size;
}				t_ast;

typedef struct s_drill
{
	int			(*f)(t_ast *, t_token **);
	enum e_lr	lr;
}				t_drill;

/*================lex.c================*/
t_bool	ms_tokenizer(t_syntax *syntax);
int		ms_count_word(const char *line, const char **op);
int		ms_get_op(const char *s1, const char **op);
int		ms_get_word(const char *line, const char **op);
int		ms_close_quote(const char *line, char quote);
char	*ms_extract_token(char *line, int *start, const char **op);
char	*ms_extract_word(char *line, int *start, const char **op);
int		ms_get_token_size(t_token **token);
/*================clear.c================*/
void	ms_clear_syntax(t_syntax *syntax);
void	ms_clear_ast(t_ast **ast);
void	ms_clear_token(t_token **token);
/*================lexer.c================*/
t_token	**ms_lexer(t_syntax *syntax);
/*================unterminal.c================*/
int		ms_is_and_or(t_ast *ast, t_token **token);
int		ms_is_pipeline(t_ast *ast, t_token **token);
int		ms_is_command(t_ast *ast, t_token **token);
int		ms_is_subshell(t_ast *ast, t_token **token);
int		ms_is_simple_command(t_ast *ast, t_token **token);
int		ms_is_redirect_list(t_ast *ast, t_token **token);
int		ms_is_io_redirect(t_ast *ast, t_token **token);
int		ms_get_op_pos(t_token **token, enum e_type op1, enum e_type op2);
/*================terminal.c================*/
int		ms_is_io_file(t_ast *ast, t_token **token);
int		ms_is_io_here(t_ast *ast, t_token **token);
int		ms_is_word(t_ast *ast, t_token **token);
/*================parser.c================*/
t_bool	ms_parser(t_ast **ast, t_token **token, int size);
t_ast	*ms_new_ast(t_token **token, int size);
int		ms_add_ast(t_ast *ast, t_token **token, int size, t_drill drill);
t_token	**ms_tokenndup(t_token **src, int size);
void	ms_parser_error_handler(t_token **token, int curtok);
t_bool	ms_set_tot_curtok(int *tot_curtok, int curtok, int expected_size);

#endif