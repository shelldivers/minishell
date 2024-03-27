#include "libft.h"
#include "ms_expand.h"
#include <gtest/gtest.h>

using namespace std;

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
	result = ms_expand_filename(argv, *env);
	EXPECT_NE(result, nullptr);
	for (int i = 0; result[i]; i++)
		cout << "result: " << result[i] << endl;
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
	result = ms_expand_filename(argv, *env);

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
	result = ms_expand_filename(argv, *env);

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
	result = ms_expand_filename(argv, *env);

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
