/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/01 19:23:22 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

// enum e_grammar
// {
// 	GNONE,
// 	GCOMPLETE_COMMAND,
// 	GPIPELINE,
// 	GSUBSHELL,
// 	GSIMPLE_COMMAND,
// 	GCMD_NAME,
// 	GCMD_WORD,
// 	GCMD_PREFIX,
// 	GCMD_SUFFIX,
// 	GIO_REDIRECT,
// 	GIO_FILE,
// 	GIO_HERE,
//	GWORD
// };

// enum e_type
// {
// 	TPIPE,
// 	TWORD,
// 	TASSIGNMENT_WORD,
// 	TAND_IF,
// 	TOR_IF,
// 	TDLESS,
// 	TDGREAT,
// 	TDREAD,
// 	TDWRITE,
// 	TSUBSHELL
// };

// typedef struct s_syntax
// {
// 	char	*line;
// 	char	**words;
// 	size_t	words_cnt;
// }				t_syntax;

// typedef struct s_token
// {
// 	enum e_type	type;
// 	char		*value;
// }				t_token;

// typedef struct s_parse
// {
// 	enum e_grammar	grammar;
// 	struct s_parser	*left;
// 	struct s_parser	*right;
// 	struct s_token	*token;
// 	size_t			token_size;
// }				t_parse;

enum t_grammar	is_cmd_suffix(t_token *token, size_t size)
{
	if (size == 1 && token[0].type == TWORD \
	&& (is_io_redirect(token, size) == GIO_REDIRECT)
		return (GCMD_SUFFIX);
	return (GNONE);
}

enum t_grammar	is_io_redirect(t_token *token, size_t size)
{
	if (size == 2 && token[1].type == TWORD \
	&& (is_io_file(token, size) == GIO_FILE \
	|| is_io_here(token, size) == GIO_HERE))
		return (GIO_REDIRECT);
	return (GNONE);
}

enum t_grammar	is_io_file(t_token *token, size_t size)
{
	if (size == 2 && token[1].type == TWORD \
	&& (token[0].type == TDLESS \
	|| token[0].type == TDWRITE \
	|| token[0].type == DGREAT))
		return (GIO_HERE);
	return (GNONE);
}

enum t_grammar	is_io_here(t_token *token, size_t size)
{
	if (size == 2 && token[1].type == TWORD \
	&& token[0].type == TDLESS)
		return (GIO_HERE);
	return (GNONE);
}

enum t_grammar	is_grammar(t_token *token, size_t size)
{
	if (is_pipeline(token, size) == GPIPELINE)
		return (GPIPELINE);
	if (is_subshell(token, size) == GSUBSHELL)
		return (GSUBSHELL);
	if (is_simple_command(token, size) == GSIMPLE_COMMAND)
		return (GSIMPLE_COMMAND);
	if (is_cmd_name(token, size) == GCMD_NAME)
		return (GCMD_NAME);
	if (is_cmd_word(token, size) == GCMD_WORD)
		return (GCMD_WORD);
	if (is_cmd_prefix(token, size) == GCMD_PREFIX)
		return (GCMD_PREFIX);
	if (is_cmd_suffix(token, size) == GCMD_SUFFIX)
		return (GCMD_SUFFIX);
	if (is_io_redirect(token, size) == GIO_REDIRECT)
		return (GIO_REDIRECT);
	if (is_io_file(token, size) == GIO_FILE)
		return (GIO_FILE);
	if (is_io_here(token, size) == GIO_HERE)
		return (GIO_HERE);
	return (GNONE);
}

void	recursive_descent_parsing(t_parse *parse_head)
{
	parse_head->grammar = is_grammar(parse_head->token, parse_head->token_size);
	if (parse_head->grammar == GNONE)
	{
		printf("Syntax error\n");
		exit(1);
	}
}

void	parse(t_parse *parse_head, t_token **token, size_t size)
{
	init_parse(parse_head, token, syntax.words_cnt);
	recursive_descent_parsing(parse_head);
}

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;
	t_token		**token;
	t_parse		*parse_head;

	init_syntax(&syntax);
	while (1)
	{
		syntax.line = readline("minishell$ ");
		if (!syntax.line)
			break ;
		add_history(syntax.line);
		lexer(&syntax);
		token = tokenize(&syntax);
		parse(parse_head, token, syntax.words_cnt);
		execute_tree(parse_head);
		clear_all(&syntax, token, parse_head);
	}
	return (0);
}
