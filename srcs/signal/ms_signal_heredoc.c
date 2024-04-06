#include "ft_printf.h"
#include "ms_signal.h"
#include <signal.h>
#include <stdlib.h>

static void	sigint(int signum);

/**
 * @signal SIGINT - Ctrl + C
 * @signal SIGQUIT - Ctrl + \
 */
void	ms_set_signal_heredoc(void)
{
	ms_set_echoctl_off();
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @signal SIGINT - Ctrl + C
 * @brief 새로운 줄에 프롬프트를 출력합니다. readline 버퍼에 문자가 있어도 동작합니다.
 *
 * @echoctl off
 * @exitcode 1
 */
static void	sigint(int signum)
{
	(void)signum;
	ft_printf("\n");
	exit(1);
}
