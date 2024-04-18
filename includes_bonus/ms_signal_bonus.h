/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:19:49 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:27:25 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNAL_BONUS_H
# define MS_SIGNAL_BONUS_H

int	g_exit;

/* ms_signal.c */
void	ms_set_signal_prompt(void);
void	sigint_prompt(int signum);

/* ms_signal_heredoc.c */
void	ms_set_signal_heredoc(void);
void	sigint_heredoc(int signum);

/* ms_signal_utils.c */
void	ms_set_echoctl_on(void);
void	ms_set_echoctl_off(void);
void	ms_set_signal_default(void);
void	ms_set_signal_ignore(void);

#endif
