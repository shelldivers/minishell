/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_macro2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:35:27 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/07 21:38:51 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_error.h"
#include "ms_exec.h"
#include "unistd.h"
#include <sys/stat.h>

int	s_isdir(int m)
{
	return (((m) & S_IFMT) == S_IFDIR);
}

void	ms_is_dir(char **words)
{
	if (ft_strchr(words[0], '/'))
	{
		if (access(words[0], F_OK & X_OK) == -1)
		{
			ms_puterror_no_file(words[0]);
			exit(127);
		}
	}
}
