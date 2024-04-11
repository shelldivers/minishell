/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:25:35 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/06 20:08:05 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"
#include <sys/wait.h>

static int	w_int(int x);

int	wifexit(int x)
{
	return ((w_int(x) & 0177) == 0);
}

int	wexitstatus(int x)
{
	return ((w_int(x) >> 8) & 0x000000ff);
}

int	wifsignaled(int x)
{
	return (wstatus(x) != _WSTOPPED && wstatus(x) != 0);
}

int	wstatus(int x)
{
	return (w_int(x) & 0177);
}

static int	w_int(int x)
{
	return (*(int *)&(x));
}
