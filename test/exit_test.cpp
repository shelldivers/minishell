#include "ms_builtin.h"
#include <gtest/gtest.h>

TEST(exit_test, basic_case)
{
	// given
	char **envp = (char *[]){"SHELL=minishell", "B=2", "C=3", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *argv[] = {"exit", "123", NULL};
	int argc = 2;

	pid_t pid = fork();
	if (pid == 0)
	{
		// when
		ms_exit(argc, argv, env);
	}
	else
	{
		// then
		int status;
		waitpid(pid, &status, 0);
		EXPECT_TRUE(WIFEXITED(status));
		EXPECT_EQ(WEXITSTATUS(status), 123);
	}
}

TEST(exit_test, no_numeric)
{
	// given
	char **envp = (char *[]){"SHELL=minishell", "B=2", "C=3", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *argv[] = {"exit", "qwe", NULL};
	int argc = 2;

	pid_t pid = fork();
	if (pid == 0)
	{
		// when
		ms_exit(argc, argv, env);
	}
	else
	{
		// then
		int status;
		waitpid(pid, &status, 0);
		EXPECT_TRUE(WIFEXITED(status));
		EXPECT_EQ(WEXITSTATUS(status), 255);
	}
}

TEST(exit_test, no_numeric_many_arg)
{
	// given
	char **envp = (char *[]){"SHELL=minishell", "B=2", "C=3", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *argv[] = {"exit", "qwe", "123", NULL};
	int argc = 2;

	pid_t pid = fork();
	if (pid == 0)
	{
		// when
		ms_exit(argc, argv, env);
	}
	else
	{
		// then
		int status;
		waitpid(pid, &status, 0);
		EXPECT_TRUE(WIFEXITED(status));
		EXPECT_EQ(WEXITSTATUS(status), 255);
	}
}

TEST(exit_test, many_args)
{
	// given
	char **envp = (char *[]){"SHELL=minishell", "B=2", "C=3", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *argv[] = {"exit", "123", "123", NULL};
	int argc = 2;

	int status = ms_exit(argc, argv, env);
	EXPECT_EQ(status, EXIT_FAILURE);
}