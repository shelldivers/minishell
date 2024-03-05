#include "ft_printf.h"
#include "libft.h"
#include "ms_expand.h"
#include <cstdlib>
#include <gtest/gtest.h>

void leakss()
{
	system("leaks minishell_test");
}

TEST(exapnd_qv_test, ms_expand_qv_dquote_test)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);
	// add complex args
	char *arg1 = ft_strdup("\\test");
	char *arg2 = ft_strdup("\\\\test");
	char *arg3 = ft_strdup("\"\\test\"");
	char *arg4 = ft_strdup("\"\\\\test\"");
	char *argv[] = {arg1, arg2, arg3, arg4, NULL};

	ms_expand(argv, env);

	for (int i = 0; argv[i]; i++)
	{
		ft_printf("%s\n", argv[i]);
	}

	ms_env_clear(env);
	free(env);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
	atexit(leakss);
}

TEST(exapnd_qv_test, ms_expand_qv_test)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);
	// add complex args
	char *arg1 = ft_strdup("hello 'world'");
	char *arg2 = ft_strdup("hello \"world\"");
	char *arg3 = ft_strdup("hello $hello");
	char *arg4 = ft_strdup("hello \\\\world\\\\");

	char *argv[] = {arg1, arg2, arg3, arg4, NULL};

	ms_expand(argv, env);

	for (int i = 0; argv[i]; i++)
	{
		printf("%s\n", argv[i]);
	}

	ms_env_clear(env);
	free(env);
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
	atexit(leakss);
}