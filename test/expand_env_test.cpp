#include "ms_expand.h"
#include "libft.h"
#include <gtest/gtest.h>

void leaks()
{
	system("leaks minishell_test");
}

TEST(exapnd_env_test, ms_expand_env_test)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *arg = ft_strdup("hello $hello");
	int i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			ms_expand_env(&arg, &i, env);
		else
			i++;
	}
	printf("%s\n", arg);
	ms_env_clear(env);
	free(env);
	free(arg);
	atexit(leaks);
}