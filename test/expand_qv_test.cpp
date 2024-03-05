#include "ms_expand.h"
#include "libft.h"
#include <gtest/gtest.h>
#include <cstdlib>

void leakss()
{
	system("leaks minishell_test");
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

	ms_expand_qv(argv, env);

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