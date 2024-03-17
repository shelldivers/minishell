/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/17 19:45:24 by jiwojung         ###   ########.fr       */
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
	if (ast->right)
		show_tree(ast->right);
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
}

void	parser(t_ast **ast, t_token **token, size_t size)
{
	t_ast	*ast;
	size_t	cursor;

	*ast = new_ast(token, size);
	cursor = add_ast(*ast, token, size, isand_or, LEFT);
	printf("cursor: %zu\n", cursor);
	if (cursor != size)
	{
		printf("syntax error %s\n", token[cursor]->value);
	}
}

void	leaks()
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;
	t_token		**token;
	t_ast		*ast;

	atexit(leaks);
	init_syntax(&syntax);
	while (1)
	{
		syntax.line = readline("minishell$ ");
		if (!(syntax.line))
			exit (1);
		add_history(syntax.line);
		lexer(&syntax);
		token = tokenize(&syntax);
		for (size_t i = 0; i < syntax.words_cnt; i++)
		{
			printf("token[%zu]: $%s$\n", i, token[i]->value);
			if (token[i]->type == TPIPE)
				printf("type: TPIPE\n");
			else if (token[i]->type == TWORD)
				printf("type: TWORD\n");
			else if (token[i]->type == TIO_NUMBER)
				printf("type: TIO_NUMBER\n");
			else if (token[i]->type == TAND_IF)
				printf("type: TAND_IF\n");
			else if (token[i]->type == TOR_IF)
				printf("type: TOR_IF\n");
			else if (token[i]->type == TDLESS)
				printf("type: TDLESS\n");
			else if (token[i]->type == TDGREAT)
				printf("type: TDGREAT\n");
			else if (token[i]->type == TDREAD)
				printf("type: TDREAD\n");
			else if (token[i]->type == TDWRITE)
				printf("type: TDWRITE\n");
			else if (token[i]->type == TLPAREN)
				printf("type: TLPAREN\n");
			else if (token[i]->type == TRPAREN)
				printf("type: TRPAREN\n");
		}
		parser(&ast, token, syntax.words_cnt);
		show_tree(ast);
		clear_all(&syntax, token, ast);
	}
	return (0);
}
