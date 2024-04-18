/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_macro2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:35:27 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 16:23:52 by jiwojung         ###   ########.fr       */
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
