#include "minishell.h"
#include <gtest/gtest.h>

TEST(pwd, basic) {
	int	argc = 1;
	char *argv[] = {"pwd"};
	char *envp[] = {"PWD=/home/user", NULL};
	int status = ms_pwd(argc, argv, envp);
	EXPECT_EQ(status, 0);
}

TEST(pwd, too_many_args) {
	int	argc = 2;
	char *argv[] = {"pwd", "test"};
	char *envp[] = {"PWD=/home/user", NULL};
	int status = ms_pwd(argc, argv, envp);
	EXPECT_EQ(status, 1);
}
