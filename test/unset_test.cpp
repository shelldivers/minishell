#include "ms_minishell.h"
#include "ms_env.h"
#include "ms_builtin.h"
#include <gtest/gtest.h>

TEST(unset_test, basic_case)
{
	// given
	char **envp = (char *[]){"A=1", "B=2", "C=3", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *argv[] = {"unset", "A", "C", NULL};
	int argc = 3;

	// when
	ms_unset(argc, argv, env);

	// then
	EXPECT_STREQ(ms_getenv(*env, "A"), NULL);
	EXPECT_STREQ(ms_getenv(*env, "B"), "2");
	EXPECT_STREQ(ms_getenv(*env, "C"), NULL);

	ms_export(1, (char *[]){"export", NULL}, env);
}

TEST(unset_test, invalid_argument)
{
	// given
	char **envp = (char *[]){"A=1", "B=2", "C=3", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *argv[] = {"unset", "!@$4", "C", NULL};
	int argc = 3;

	// when
	ms_unset(argc, argv, env);

	// then
	EXPECT_STREQ(ms_getenv(*env, "A"), "1");
	EXPECT_STREQ(ms_getenv(*env, "B"), "2");
	EXPECT_STREQ(ms_getenv(*env, "C"), NULL);

	ms_export(1, (char *[]){"export", NULL}, env);
}