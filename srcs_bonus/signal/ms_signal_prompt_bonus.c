/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_prompt_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:38:53 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 20:32:55 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ms_signal_bonus.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

void	ms_set_signal_prompt(void)
{
	ms_set_echoctl_off();
	signal(SIGINT, sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_prompt(int signum)
{
	(void)signum;
	ft_dprintf(STDERR_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit = 1;
}
