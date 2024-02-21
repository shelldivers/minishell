#include "minishell.h"
#include <gtest/gtest.h>

TEST(echo, basic_case)
{
	char *argv[] = {"echo", "Hello", "World", NULL};
	int argc = 3;
	ms_echo(argc, argv);
	ms_echo(argc, argv);
}

TEST(echo, with_option)
{
	char *argv[] = {"echo", "-n", "Hello", "World!", NULL};
	int argc = 4;
	ms_echo(argc, argv);
	ms_echo(argc, argv);
}

TEST(echo, invalid_option)
{
	char *argv[] = {"echo", "-e", "Hello", "World!", NULL};
	int argc = 4;
	ms_echo(argc, argv);
}

TEST(echo, no_argv)
{
	char *argv[] = {"echo", NULL};
	int argc = 1;
	ms_echo(argc, argv);
}
