/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:24:28 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/11 19:12:42 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ms_parser.h"
#include "libft.h"
#include "ms_error.h"

void	ms_parser(t_ast **ast, t_token **token, int size)
{
	int	curtok;

	*ast = ms_new_ast(token, size);
	if (!*ast)
	{
		ms_puterror_cmd(NULL, "malloc");
		return ;
	}
	curtok = ms_add_ast(*ast, token, size, (t_drill){ms_is_and_or, LEFT});
	if (curtok == -1)
	{
		ms_puterror_cmd(NULL, "malloc");
		ms_clear_ast(ast);
		return ;
	}
	else if (curtok != size)
	{
		ms_parser_error_handler(token, curtok);
		ms_clear_ast(ast);
	}
}
