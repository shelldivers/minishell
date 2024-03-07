/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:24:17 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/07 16:57:02 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// # include "ft_bool.h"
// # include "ms_env.h"

# include <stdlib.h>

enum e_grammar
{
	GAND_OR,
	GPIPELINE,
	GCOMMAND,
	GSUBSHELL,
	GSIMPLE_COMMAND,
	GCMD_SUFFIX,
	GREDIRECT_LIST,
	GIO_REDIRECT,
	GIO_FILE,
	GIO_HERE,
	GWORD,
	GNONE
};

enum e_op
{
	OPPIPE,
	OPAND_IF,
	OPOR_IF,
	OPSUBSHELL,
	OPIO_HERE,
	OPIO_FILE,
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
	enum e_op		op;
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
void	backtracking_free(t_parse **parse);
/*================tokenize.c================*/
t_token	**tokenize(t_syntax *syntax);
/*================is_grammar.c================*/
size_t	isio_here(t_parse *parse, t_token **token);
size_t	isio_file(t_parse *parse, t_token **token);
size_t	isio_redirect(t_parse *parse, t_token **token);
size_t	isredirect_list(t_parse *parse, t_token **token);
size_t	iscmd_suffix(t_parse *parse, t_token **token);
size_t	issimple_command(t_parse *parse, t_token **token);
size_t	issubshell(t_parse *parse, t_token **token);
size_t	iscommand(t_parse *parse, t_token **token);
size_t	ispipeline(t_parse *parse, t_token **token);
size_t	isand_or(t_parse *parse, t_token **token);
size_t	isword(t_parse *parse, t_token **token);
/*================parse_tree.c================*/
t_parse	*ms_new_parse(t_token **token, enum e_op op, size_t size);
#endif