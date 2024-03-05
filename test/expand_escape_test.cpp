#include "ms_expand.h"
#include "libft.h"
#include <gtest/gtest.h>


TEST(exapnd_escape_test, ms_expand_escape_test)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *arg = ft_strdup("h\"el\\lo world\'");
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

TEST(exapnd_escape_test, ms_expand_escape)
{
	char *arg = ft_strdup("\\\\ \\\\ \\\\ \\\\");
	int i = 0;
	while (arg[i])
	{
		if (arg[i] == '\\')
			ms_expand_escape(arg, &i);
		else
			i++;
	}
	printf("%s\n", arg);
}
