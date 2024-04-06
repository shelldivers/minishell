#include "ft_printf.h"
#include "ms_signal.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

/**
 * @signal SIGINT - Ctrl + C
 * @signal SIGTERM - Ctrl + D
 * @signal SIGQUIT - Ctrl + \
 */
void	ms_set_signal_prompt(void)
{
	ms_set_echoctl_off();
	signal(SIGINT, sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @signal SIGINT - Ctrl + C
 * @brief 새로운 줄에 프롬프트를 출력합니다. readline 버퍼에 문자가 있어도 동작합니다.
 *
 * @echoctl off
 * @exitcode 1
 */
void	sigint_prompt(int signum)
{
	(void)signum;
	ft_dprintf(STDERR_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit = 1;
}
