#include "libft.h"
#include "ms_expand.h"
#include "ms_error.h"
#include <gtest/gtest.h>

using namespace std;

TEST(ms_filename_test, ms_filename_test16)
{
	char *argv[3];
	t_env **env;
	char **result;
	char *input = "*u/././*";	// input

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup(input);
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	cout << endl;
	EXPECT_NE(result, nullptr);
	int count = 0;
	for (int i = 0; result[i]; i++, count++)
		cout << "result: " << result[i] << endl;
	cout << endl;
	cout << "count: " << count - 1 << endl;

	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test15)
{
	char *argv[3];
	t_env **env;
	char **result;
	char *input = "*/arc";	// input

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup(input);
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	cout << endl;
	EXPECT_NE(result, nullptr);
	int count = 0;
	for (int i = 0; result[i]; i++, count++)
		cout << "result: " << result[i] << endl;
	cout << endl;
	cout << "count: " << count - 1 << endl;

	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test14)
{
	char *argv[3];
	t_env **env;
	char **result;
	char *input = "/////*/*////*";	// input

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup(input);
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	cout << endl;
	EXPECT_EQ(result, nullptr);

	ms_puterror_arg(*env, *argv);

	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test13)
{
	char *argv[3];
	t_env **env;
	char **result;
	char *input = "u*//////l*";	// input

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup(input);
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	cout << endl;
	EXPECT_NE(result, nullptr);
	for (int i = 0; result[i]; i++)
		cout << "result: " << result[i] << endl;
	cout << endl;

	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test12)
{
	char *argv[3];
	t_env **env;
	char **result;
	char *input = "///////////////////////////*";	// input

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup(input);
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	cout << endl;
	EXPECT_NE(result, nullptr);
	for (int i = 0; result[i]; i++)
		cout << "result: " << result[i] << endl;
	cout << endl;

	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test11)
{
	char *argv[3];
	t_env **env;
	char **result;
	char *input = "\"u\"*";	// input

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup(input);
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	cout << endl;
	EXPECT_NE(result, nullptr);
	for (int i = 0; result[i]; i++)
		cout << "result: " << result[i] << endl;
	cout << endl;

	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test10)
{
	char *argv[3];
	t_env **env;
	char **result;
	char *input = "\"*\"";	// input

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup(input);
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	cout << endl;
	EXPECT_NE(result, nullptr);
	for (int i = 0; result[i]; i++)
		cout << "result: " << result[i] << endl;
	cout << endl;

	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test)
{
	char *argv[3];
	t_env **env;
	char **result;

	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		nullptr,
	};

	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("srcs/*");
	argv[2] = nullptr;
	result = ms_expand_filenames(argv);

	cout << endl;
	EXPECT_NE(result, nullptr);
	for (int i = 0; result[i]; i++)
		cout << "result: " << result[i] << endl;
	cout << endl;

	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test3)
{
	char *argv[3];
	t_env **env;
	char **result;

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("./u*");
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	cout << endl;
	EXPECT_NE(result, nullptr);
	for (int i = 0; result[i]; i++)
		cout << "result: " << result[i] << endl;
	cout << endl;

	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test9)
{
	char *argv[3];
	t_env **env;
	char **result;

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup(".*");
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	int count = 0;
	EXPECT_NE(result, nullptr);
	for (int i = 0; result[i]; i++, count++)
		cout << "result: " << result[i] << endl;
	cout << "count: " << count - 1 << endl;
	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test8)
{
	char *argv[3];
	t_env **env;
	char **result;

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("*/");
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	int count = 0;
	EXPECT_NE(result, nullptr);
	for (int i = 0; result[i]; i++, count++)
		cout << "result: " << result[i] << endl;
	cout << "count: " << count - 1 << endl;
	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test5)
{
	char *argv[3];
	t_env **env;
	char **result;

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("*");
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	EXPECT_NE(result, nullptr);
	for (int i = 0; result[i]; i++)
		cout << "result: " << result[i] << endl;

	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test4)
{
	char *argv[3];
	t_env **env;
	char **result;

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("u*/l*/a*");
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	EXPECT_NE(result, nullptr);
	for (int i = 0; result[i]; i++)
		cout << "result: " << result[i] << endl;

	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}

TEST(ms_filename_test, ms_filename_test2)
{
	char *argv[3];
	t_env **env;
	char **result;

	// given
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL,
	};
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("u*");
	argv[2] = NULL;

	// when
	result = ms_expand_filenames(argv);

	// then
	EXPECT_NE(result, nullptr);
	for (int i = 0; result[i]; i++)
		cout << "result: " << result[i] << endl;

	// final
	ms_env_clear(env);
	free(env);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
}
