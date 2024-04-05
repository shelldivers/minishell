/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:25:35 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/05 14:03:50 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "ms_minishell.h"

static int	w_int(int x);

int	wifexit(int x)
{
	return ((w_int(x) & 0177) == 0);
}


int	wexitstatus(int x)
{
	return ((w_int(x) >> 8) & 0x000000ff);
}

static int	w_int(int x)
{
	return (*(int *)&(x));
}
