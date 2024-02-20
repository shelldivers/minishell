#include "minishell.h"
#include <gtest/gtest.h>

TEST(echo, basic_case)
{
	char *argv[] = {"echo", "Hello", "World", NULL};
	int argc = 3;
	echo(argc, argv);
	echo(argc, argv);
}

TEST(echo, with_option)
{
	char *argv[] = {"echo", "-n", "Hello", "World!", NULL};
	int argc = 4;
	echo(argc, argv);
	echo(argc, argv);
}

TEST(echo, invalid_option)
{
	char *argv[] = {"echo", "-e", "Hello", "World!", NULL};
	int argc = 4;
	echo(argc, argv);
}
