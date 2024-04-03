#include "libft.h"
#include "ms_expand.h"
#include <gtest/gtest.h>

using namespace std;

TEST(ms_expand_test, basic_case5) // TODO : Failed to parse content
{
	char *argv[3];
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		"a=\'asd",
		NULL
	};
	t_env **env;
	int status;
	status = 0;
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("\"$HOME\\\"\"");	// ???
	argv[2] = NULL;

	char **result = ms_expansion(argv, *env, status);
	EXPECT_NE(result, nullptr);
	cout << endl;
	int count = 0;
	for (int i = 0; result[i]; i++, count++)
		cout << "result[" << i << "]: " << result[i] << endl;
	cout << "count: " << count - 1 << endl;
	cout << endl;

	ms_env_clear(env);
	free(env);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
}

TEST(ms_expand_test, basic_case4) // TODO : Failed to parse content
{
	char *argv[3];
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		"a=\'asd",
		NULL
	};
	t_env **env;
	int status;
	status = 0;
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("$a@");	// ???
	argv[2] = NULL;

	char **result = ms_expansion(argv, *env, status);
	EXPECT_NE(result, nullptr);
	cout << endl;
	int count = 0;
	for (int i = 0; result[i]; i++, count++)
		cout << "result[" << i << "]: " << result[i] << endl;
	cout << "count: " << count - 1 << endl;
	cout << endl;

	ms_env_clear(env);
	free(env);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
}

TEST(ms_expand_test, basic_case3)
{
	char *argv[3];
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL
	};
	t_env **env;
	int status;
	status = 0;
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("\"/Users/jeongwpa/\"*p*jct*");
	argv[2] = NULL;

	char **result = ms_expansion(argv, *env, status);
	EXPECT_NE(result, nullptr);
	cout << endl;
	int count = 0;
	for (int i = 0; result[i]; i++, count++)
		cout << "result[" << i << "]: " << result[i] << endl;
	cout << "count: " << count - 1 << endl;
	cout << endl;

	ms_env_clear(env);
	free(env);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
}

TEST(ms_expand_test, basic_case2)
{
	char *argv[3];
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL
	};
	t_env **env;
	int status;
	status = 0;
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("\"/Users/jeongwpa/\"\"pro\"*");
	argv[2] = NULL;

	char **result = ms_expansion(argv, *env, status);
	EXPECT_NE(result, nullptr);
	cout << endl;
	int count = 0;
	for (int i = 0; result[i]; i++, count++)
		cout << "result[" << i << "]: " << result[i] << endl;
	cout << "count: " << count - 1 << endl;
	cout << endl;

	ms_env_clear(env);
	free(env);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
}

TEST(ms_expand_test, basic_case)
{
	char *argv[3];
	char *envp[] = {
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"HOME=/Users/jeongwpa",
		"LOGNAME=jeongwpa",
		NULL
	};
	t_env **env;
	int status;
	status = 0;
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("\"/Users/jeongwpa/*\"*");
	argv[2] = NULL;

	char **result = ms_expansion(argv, *env, status);
	EXPECT_NE(result, nullptr);
	cout << endl;
	int count = 0;
	for (int i = 0; result[i]; i++, count++)
		cout << "result[" << i << "]: " << result[i] << endl;
	cout << "count: " << count - 1 << endl;
	cout << endl;

	ms_env_clear(env);
	free(env);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
}