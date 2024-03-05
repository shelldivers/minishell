#include "minishell.h"
#include "ms_builtin.h"
#include <gtest/gtest.h>

TEST(export_test, basic_case)
{
	// given
	char *argv[] = {"export", "HELLO=WORLD", NULL};
	int argc = 2;
	t_env *env = NULL;

	// when
	ms_export(argc, argv, &env);

	// then
	EXPECT_STREQ(ms_getenv(env, "HELLO"), "WORLD");
}

TEST(export_test, no_argument)
{
	// given
	char *argv[] = {"export", NULL};
	int argc = 1;
	char *envp1 = "HELLO=WORLD";
	char *envp2 = "GOODBYE=PARK";
	char *envp3 = "HELLO1=PARK";
	char *envp4 = "GOODBYE2=WORLD";
	char *envp5 = "HELLO3=";
	char *envp[10] = {envp1, envp2, envp3, envp4, envp5, NULL};
	t_env **env = ms_env_deserialize(envp);

	// when
	ms_export(argc, argv, env);
}

TEST(export_test, no_equal_sign)
{
	// given
	char *argv[] = {"export", "HELLO", NULL};
	int argc = 2;
	t_env *env = NULL;

	// when
	ms_export(argc, argv, &env);

	// then
	EXPECT_EQ(ms_getenv(env, "HELLO"), (void *)0);
}

TEST(export_test, empty_argument)
{
	// given
	char *argv[] = {"export", "", "HELLO=WORLD", NULL};
	int argc = 3;
	t_env *env = NULL;

	// when
	ms_export(argc, argv, &env);

	// then
	// error message must be printed and HELLO must be exported
	EXPECT_STREQ(ms_getenv(env, "HELLO"), "WORLD");
}

TEST(export_test, empty_value)
{
	// given
	char *argv[] = {"export", "EMPTY=", "HELLO=WORLD", NULL};
	int argc = 3;
	t_env *env = NULL;

	// when
	ms_export(argc, argv, &env);

	// then
	EXPECT_STREQ(ms_getenv(env, "EMPTY"), "");
	EXPECT_STREQ(ms_getenv(env, "HELLO"), "WORLD");
}

TEST(export_test, empty_only_key)
{
	// given
	char *argv[] = {"export", "NOVAL", "HELLO=WORLD", NULL};
	int argc = 3;
	t_env *env = NULL;

	// when
	ms_export(argc, argv, &env);

	// then
	EXPECT_EQ(ms_getenv(env, "NOVAL"), nullptr);
	EXPECT_STREQ(ms_getenv(env, "HELLO"), "WORLD");
}

TEST(export_test, empty_key_value)
{
	// given
	char *argv[] = {"export", "=", "HELLO=WORLD", NULL};
	char *argv1[] = {"export", NULL};
	int argc = 3;
	t_env *env = NULL;

	// when
	ms_export(argc, argv, &env);
	ms_export(1, argv1, &env);

	// then
	EXPECT_STREQ(ms_getenv(env, "HELLO"), "WORLD");
}

TEST(export_test, invalid_key)
{
	// given
	char *argv[] = {"export", "1TEST=test", "HELLO=WORLD", NULL};
	char *argv1[] = {"export", NULL};
	int argc = 3;
	t_env *env = NULL;

	// when
	ms_export(argc, argv, &env);
	ms_export(1, argv1, &env);

	// then
	EXPECT_STREQ(ms_getenv(env, "HELLO"), "WORLD");
}

TEST(export_test, underscore_key)
{
	// given
	char *argv[] = {"export", "_TEST_=test", "HELLO=WORLD", NULL};
	char *argv1[] = {"export", NULL};
	int argc = 3;
	t_env *env = NULL;

	// when
	ms_export(argc, argv, &env);
	ms_export(1, argv1, &env);

	// then
	EXPECT_STREQ(ms_getenv(env, "_TEST_"), "test");
	EXPECT_STREQ(ms_getenv(env, "HELLO"), "WORLD");
}

TEST(export_test, many_arguments)
{
	// given
	char *argv[] = {"export", "HELLO=WORLD", "GOODBYE=PARK", "HELLO=PARK", "GOODBYE=WORLD", "NOARG", "EMPTY=", "", NULL};
	char *argv1[] = {"export", NULL};
	int argc = 8;
	t_env *env = NULL;

	// when
	ms_export(argc, argv, &env);
	ms_export(argc, argv1, &env);

	// then
	EXPECT_STREQ(ms_getenv(env, "HELLO"), "PARK");
	EXPECT_STREQ(ms_getenv(env, "GOODBYE"), "WORLD");
}

TEST(export_test, overwrite)
{
	// given
	char *argv[] = {"export", "HELLO=WORLD", "HELLO=PARK", NULL};
	int argc = 3;
	t_env *env = NULL;

	// when
	ms_export(argc, argv, &env);

	// then
	EXPECT_STREQ(ms_getenv(env, "HELLO"), "PARK");
}

TEST(export_test, qwer)
{
	// given
	char *argv[] = {"export", "NOVAL", "QWER=qwer", "Q=1", "W=2", "E=3", NULL};
	int argc = 3;
	t_env *env = NULL;

	// when
	ms_export(argc, argv, &env);

	// then
	EXPECT_EQ(ms_getenv(env, "NOVAL"), (void *)0);
	EXPECT_STREQ(ms_getenv(env, "QWER"), "qwer");
	EXPECT_STREQ(ms_getenv(env, "Q"), "1");
	EXPECT_STREQ(ms_getenv(env, "W"), "2");
	EXPECT_STREQ(ms_getenv(env, "E"), "3");

	printf("env: %s\n", ms_getenv(env, "NOVAL"));
	printf("env: %s\n", ms_getenv(env, "QWER"));
	printf("env: %s\n", ms_getenv(env, "Q"));
	printf("env: %s\n", ms_getenv(env, "W"));
	printf("env: %s\n", ms_getenv(env, "E"));
}