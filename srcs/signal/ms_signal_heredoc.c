/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:38:50 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/06 20:38:51 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_signal.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	ms_set_signal_heredoc(void)
{
	ms_set_echoctl_off();
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_heredoc(int signum)
{
	(void)signum;
	ft_dprintf(STDERR_FILENO, "\n");
	g_exit = 1;
	exit(g_exit);
}
