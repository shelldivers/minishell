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

/**
 * @brief execve를 호출하기 전에 기본 시그널을 설정합니다.\n
 * @brief 자식 프로세스가 실행되는 동안 부모 프로세스는 시그널을 받지 않아야 합니다.
 */
void	ms_set_signal_default(void)
{
	ms_set_echoctl_on();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief execve를 호출하고 자식 프로세스가 종료될 때까지 부모 프로세스는 시그널을 받지 않아야 합니다.\n
 * @brief 자식 프로세스가 종료된 후 시그널을 재설정 해야합니다.
 */
void	ms_set_signal_ignore(void)
{
	ms_set_echoctl_off();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
