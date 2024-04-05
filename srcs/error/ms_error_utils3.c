/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:50:25 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/05 21:06:48 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_error.h"
#include "ms_env.h"
#include <sys/errno.h>

void	ms_puterror_ambiguous_redirect(char *path)
{
	const char	*msg = "ambiguous redirect";

	ft_dprintf(2, "minishell: %s: %s\n", path, msg);
	errno = 0;
}

void	ms_puterror_syntax_newline(void)
{
	const char	*msg = "syntax error near unexpected token `newline'";

	ft_dprintf(2, "minishell: %s\n", msg);
	errno = 0;
}
