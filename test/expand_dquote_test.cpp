#include "ms_expand.h"
#include "libft.h"
#include <gtest/gtest.h>


TEST(exapnd_dquote_test, ms_expand_dquote_test)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *arg = ft_strdup("\"hello world\"");
	int i = 0;
	while (arg[i])
	{
		if (arg[i] == '\"')
			ms_expand_dquote(arg, &i, env);
		else
			i++;
	}
	printf("%s\n", arg);
}