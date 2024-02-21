#include "minishell.h"
#include <gtest/gtest.h>

TEST(pwd, basic) {
	int	argc = 1;
	char *argv[] = {"pwd"};
	EXPECT_EQ(ms_pwd(argc, argv), 0);
}

TEST(pwd, too_many_args) {
	int	argc = 2;
	char *argv[] = {"pwd", "test"};
	int result = ms_pwd(argc, argv);
	EXPECT_EQ(result, 1);
}
