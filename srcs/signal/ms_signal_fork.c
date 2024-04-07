/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:38:46 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/06 20:38:47 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_signal.h"
#include <unistd.h>
#include <signal.h>

void	ms_set_signal_fork(void)
{
	ms_set_echoctl_on();
	signal(SIGINT, sigint_fork);
	signal(SIGQUIT, sigquit_fork);
}

void	sigint_fork(int signum)
{
	(void)signum;
	ft_dprintf(STDERR_FILENO, "\n");
	g_exit = 128 + signum;
}

void	sigquit_fork(int signum)
{
	(void)signum;
	ft_dprintf(STDERR_FILENO, "Quit: 3\n");
	g_exit = 128 + signum;
}
