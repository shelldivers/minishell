/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/19 19:48:46 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	show_tree(t_ast *ast)
{
	int	i;

	i = 0;
	if (!ast)
		return ;
	if (ast->left)
		show_tree(ast->left);
	printf ("=================================\n");
	printf("token size: %zu\n", ast->token_size);
	if (ast->grammar == GAND_OR)
		printf("grammar: GAND_OR\n");
	else if (ast->grammar == GPIPELINE)
		printf("grammar: GPIPELINE\n");
	else if (ast->grammar == GCOMMAND)
		printf("grammar: GCOMMAND\n");
	else if (ast->grammar == GSUBSHELL)
		printf("grammar: GSUBSHELL\n");
	else if (ast->grammar == GSIMPLE_COMMAND)
		printf("grammar: GSIMPLE_COMMAND\n");
	else if (ast->grammar == GCMD_SUFFIX)
		printf("grammar: GCMD_SUFFIX\n");
	else if (ast->grammar == GCMD_PREFIX)
		printf("grammar: GCMD_PREFIX\n");
	else if (ast->grammar == GIO_REDIRECT)
		printf("grammar: GIO_REDIRECT\n");
	else if (ast->grammar == GIO_FILE)
		printf("grammar: GIO_FILE\n");
	else if (ast->grammar == GIO_HERE)
		printf("grammar: GIO_HERE\n");
	else if (ast->grammar == GWORD)
		printf("grammar: GWORD\n");
	else if (ast->grammar == GIO_NUMBER)
		printf("grammar: GIO_NUMBER\n");
	else if (ast->grammar == GFILENAME)
		printf("grammar: GFILENAME\n");
	else if (ast->grammar == GHERE_END)
		printf("grammar: GHERE_END\n");
	else if (ast->grammar == GCMD_NAME)
		printf("grammar: GCMD_NAME\n");
	else if (ast->grammar == GCMD_WORD)
		printf("grammar: GCMD_WORD\n");
	else if (ast->grammar == GNONE)
		printf("grammar: GNONE\n");
	if (ast->op == OPAND_IF)
		printf("op: OPAND_IF\n");
	else if (ast->op == OPOR_IF)
		printf("op: OPOR_IF\n");
	else if (ast->op == OPPIPE)
		printf("op: OPPIPE\n");
	else if (ast->op == OPNONE)
		printf("op: OPNONE\n");
	printf("token: ");
	while (i < ast->token_size)
	{
		printf("%s  ", ast->token[i]->value);
		i++;
	}
	printf("\n");
	if (ast->right)
		show_tree(ast->right);
}

void	parser(t_ast *ast, t_token **token, size_t size)
{
	size_t	cursor;

	ast = new_ast(token, size);
	if (!ast)
	{
		printf("invalid line\n");
		return ;
	}
	ast->grammar = GAND_OR;
	cursor = add_ast(ast, token, isand_or, size, LEFT);
	show_tree(ast);
	printf("cursor: %zu\n", cursor);
	if (cursor != size)
	{
		printf("syntax error %s\n", token[cursor]->value);
	}
	clear_ast(ast);
	clear_token(token);
}

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;
	t_token		**token;
	t_ast		*ast;

	init_syntax(&syntax);
	while (1)
	{
		syntax.line = readline("minishell$ ");
		if (!(syntax.line))
			exit (1);
		add_history(syntax.line);
		lexer(&syntax);
		token = tokenize(&syntax);
		parser(ast, token, syntax.words_cnt);
		clear_syntax(&syntax);
	}
	return (0);
}
