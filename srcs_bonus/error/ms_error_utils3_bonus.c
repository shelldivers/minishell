/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_utils3_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:50:25 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:29:26 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_error_bonus.h"
#include "ms_env_bonus.h"
#include "ms_signal_bonus.h"
#include <sys/errno.h>

void	ms_puterror_ambiguous_redirect(char *path)
{
	const char	*msg = "ambiguous redirect";

	ft_dprintf(2, "%s: %s: %s\n", MINISHELL, path, msg);
	errno = 0;
	g_exit = 1;
}

void	ms_puterror_syntax_newline(void)
{
	const char	*msg = "syntax error near unexpected token `newline'";

	ft_dprintf(2, "%s: %s\n", MINISHELL, msg);
	errno = 0;
	g_exit = 258;
}

void	ms_puterror_permission_denied(char *path)
{
	const char	*msg = "permission denied";

	ft_dprintf(2, "%s: %s: %s\n", MINISHELL, path, msg);
	errno = 0;
	g_exit = 126;
}
