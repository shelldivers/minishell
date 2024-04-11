/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:38:56 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/06 20:39:05 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_signal.h"
#include <termios.h>
#include <unistd.h>
#include <signal.h>

void	ms_set_echoctl_off(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, STDIN_FILENO, &term);
}

void	ms_set_echoctl_on(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag |= (ECHOCTL);
	tcsetattr(STDOUT_FILENO, STDIN_FILENO, &term);
}

void	ms_set_signal_default(void)
{
	ms_set_echoctl_on();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ms_set_signal_ignore(void)
{
	ms_set_echoctl_off();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
