/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:35:18 by jiwojung          #+#    #+#             */
/*   Updated: 2024/02/25 18:54:52 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_syntax	syntax;

	while (1)
    {
        syntax.line = readline("prompt : ");
        if (syntax.line && *syntax.line)
		{
            add_history(syntax.line);
			separate_words(&syntax);
		}
		free(syntax.line);
		syntax.line = NULL;
    }
	return (0);
}
