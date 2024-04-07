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

/**
 * @signal SIGINT - Ctrl + C
 * @signal SIGQUIT - Ctrl + \
 */
void	ms_set_signal_heredoc(void)
{
	ms_set_echoctl_off();
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @signal SIGINT - Ctrl + C
 * @brief 새로운 줄에 프롬프트를 출력합니다. readline 버퍼에 문자가 있어도 동작합니다.
 *
 * @echoctl off
 * @exitcode 1
 */
void	sigint_heredoc(int signum)
{
	(void)signum;
	ft_dprintf(STDERR_FILENO, "\n");
	g_exit = 1;
	exit(g_exit);
}
