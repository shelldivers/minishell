/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/09 15:47:28 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

// void	show_tree(t_parse *parse)
// {
// 	int	i;

// 	i = 0;
// 	if (!parse)
// 		return ;
// 	if (parse->left)
// 		show_tree(parse->left);
// 	if (parse->right)
// 		show_tree(parse->right);
// 	printf ("=================================\n");
// 	printf("token size: %zu\n", parse->token_size);
// 	if (parse->grammar == GAND_OR)
// 		printf("grammar: GAND_OR\n");
// 	else if (parse->grammar == GPIPELINE)
// 		printf("grammar: GPIPELINE\n");
// 	else if (parse->grammar == GCOMMAND)
// 		printf("grammar: GCOMMAND\n");
// 	else if (parse->grammar == GSUBSHELL)
// 		printf("grammar: GSUBSHELL\n");
// 	else if (parse->grammar == GSIMPLE_COMMAND)
// 		printf("grammar: GSIMPLE_COMMAND\n");
// 	else if (parse->grammar == GCMD_SUFFIX)
// 		printf("grammar: GCMD_SUFFIX\n");
// 	else if (parse->grammar == GCMD_PREFIX)
// 		printf("grammar: GCMD_PREFIX\n");
// 	else if (parse->grammar == GIO_REDIRECT)
// 		printf("grammar: GIO_REDIRECT\n");
// 	else if (parse->grammar == GIO_FILE)
// 		printf("grammar: GIO_FILE\n");
// 	else if (parse->grammar == GIO_HERE)
// 		printf("grammar: GIO_HERE\n");
// 	else if (parse->grammar == GWORD)
// 		printf("grammar: GWORD\n");
// 	if (parse->op == OPAND_IF)
// 		printf("op: OPAND_IF\n");
// 	else if (parse->op == OPOR_IF)
// 		printf("op: OPOR_IF\n");
// 	else if (parse->op == OPPIPE)
// 		printf("op: OPPIPE\n");
// 	else if (parse->op == OPNONE)
// 		printf("op: OPNONE\n");
// 	printf("token: ");
// 	while (i < parse->token_size)
// 	{
// 		printf("%s  ", parse->token[i]->value);
// 		i++;
// 	}
// 	printf("\n");
// }

// void	parser(t_parse **parse, t_token **token, size_t size)
// {
// 	size_t	i;

// 	*parse = ms_new_parse(token, OPNONE, size);
// 	init_parse(*parse, token, size);
// 	i = isand_or(*parse, token);
// 	backtracking_free(parse);
// 	printf("i: %zu\n", i);
// 	if (i != size)
// 	{
// 		printf("syntax error %s\n", token[i]->value);
// 	}
// }

// t_parse	*ms_new_parse(t_token **token, enum e_op op, size_t size)
// {
// 	t_parse	*new_parse;

// 	new_parse = (t_parse *)malloc(sizeof(t_parse));
// 	new_parse->token = token;
// 	new_parse->token_size = size;
// 	new_parse->grammar = GNONE;
// 	new_parse->op = op;
// 	new_parse->left = NULL;
// 	new_parse->right = NULL;
// 	return (new_parse);
// }

void	leaks()
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;
	t_token		**token;
	t_parse		*parse;

	atexit(leaks);
	init_syntax(&syntax);
	while (1)
	{
		syntax.line = readline("minishell$ ");
		if (!(syntax.line))
			exit (1);
		add_history(syntax.line);
		lexer(&syntax);
		printf ("=================================\n");
		printf ("words_cnt: %zu\n", syntax.words_cnt);
		token = tokenize(&syntax);
		for (size_t i = 0; token[i]; i++)
		{
			printf ("\n=================================\n\n");
			printf("token[%zu]: $%s$\n", i, token[i]->value);
			if (token[i]->type == TAND_IF)
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
			else if (token[i]->type == TLBRACE)
				printf("type: TLBRACE\n");
			else if (token[i]->type == TRBRACE)
				printf("type: TRBRACE\n");
			else if (token[i]->type == TWORD)
				printf("type: TWORD\n");
			else if (token[i]->type == TPIPE)
				printf("type: TPIPE\n");
		}
		// parser(&parse, token, syntax.words_cnt);
		// show_tree(parse);
		clear_all(&syntax, token, parse);
	}
	return (0);
}
