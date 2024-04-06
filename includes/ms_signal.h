#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

int	g_exit;

/* ms_signal.c */
void	ms_set_signal_prompt(void);

/* ms_signal_heredoc.c */
void	ms_set_signal_heredoc(void);

/* ms_signal_fork.c */
void	ms_set_signal_fork(void);

/* ms_signal_utils.c */
void	ms_set_echoctl_on(void);
void	ms_set_echoctl_off(void);
void	set_exitcode(int code);
void	ms_set_signal_default(void);
void	ms_set_signal_ignore(void);

#endif
