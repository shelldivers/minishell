/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:24:28 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 20:32:19 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser_bonus.h"
#include "ms_error_bonus.h"
#include <stdio.h>

t_bool	ms_parser(t_ast **ast, t_token **token, int size)
{
	int	curtok;

	*ast = ms_new_ast(token, size);
	if (!*ast)
	{
		ms_puterror_cmd(NULL, "malloc");
		return (FALSE);
	}
	curtok = ms_add_ast(*ast, token, size, (t_drill){ms_is_and_or, LEFT});
	if (curtok == -1)
	{
		ms_puterror_cmd(NULL, "malloc");
		return (FALSE);
	}
	else if (curtok != size)
	{
		ms_parser_error_handler(token, curtok);
		return (FALSE);
	}
	return (TRUE);
}
