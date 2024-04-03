#include "gtest/gtest.h"

void	leaks()
{
	system("leaks minishell_test");
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	atexit(leaks);
	return RUN_ALL_TESTS();
}