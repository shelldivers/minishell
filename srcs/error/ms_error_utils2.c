/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:50:25 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/05 21:03:04 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_error.h"
#include "ms_env.h"
#include <sys/errno.h>

void	ms_puterror_is_dir(char *path)
{
	const char	*msg = "is a directory";

	ft_dprintf(2, "minishell: %s: %s\n", path, msg);
	errno = 0;
}

void	ms_puterror_no_file(char *path)
{
	const char	*msg = "No such file or directory";

	ft_dprintf(2, "minishell: %s: %s\n", path, msg);
	errno = 0;
}

void	ms_puterror_fork(void)
{
	const char	*msg = "fork failed";

	ft_dprintf(2, "minishell: %s\n", msg);
	errno = 0;
}

void	ms_puterror_max_here_doc(void)
{
	const char	*msg = "maximum here-document count exceeded";

	ft_dprintf(2, "minishell: %s\n", msg);
	errno = 0;
}

void	ms_puterror_no_command(char *path)
{
	const char	*msg = "command not found";

	ft_dprintf(2, "minishell: %s: %s\n", path, msg);
	errno = 0;
}
