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
	g_exit = 131;
}
