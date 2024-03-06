#include "ms_expand.h"
#include "libft.h"
#include <gtest/gtest.h>

void leaks();

TEST(exapnd_env_test, ms_expand_env_test)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *arg = ft_strdup("hello $hello");
	char *argv[] = {arg, NULL};
	t_list **lst = ms_expand_init(argv);
	int i = 0;
	char **str = (char **)&(*lst)->content;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
			ms_expand_env(lst, lst, &i, env);
		else
			i++;
	}
	EXPECT_STREQ("hello world", *str);
	printf("%s\n", *str);
	free(arg);
	ft_lstclear(lst, free);
	free(lst);
	ms_env_clear(env);
	free(env);
}