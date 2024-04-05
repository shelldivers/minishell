/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_error_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:31:42 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 16:40:10 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"
#include "ms_error.h"

void	ms_parser_error_handler(t_token **token, int curtok)
{
	char		*err_val;
	enum e_type	err_type;

	err_type = token[curtok]->type;
	err_val = token[curtok]->value;
	if (err_type == TDLESS || err_type == TDGREAT \
	|| err_type == TDREAD || err_type == TDWRITE)
	{
		if (!token[curtok + 1])
		{
			ms_puterror_syntax_newline();
			return ;
		}
		else
			err_val = token[curtok + 1]->value;
	}
	else
		err_val = token[curtok]->value;
	ms_puterror_syntax(NULL, err_val);
}
