#include "ms_expand.h"
#include "libft.h"
#include <gtest/gtest.h>
#include <cstdlib>

void leaks(void)
{
	system("leaks minishell_test");
}

TEST(exapnd_dquote_test, ms_expand_dquote_test1)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *arg = ft_strdup("\"hello world\"");
	char *argv[] = {"ls", arg, NULL};

	t_list **lst = ms_expand_init(argv);
	int i = 0;
	char *str = (char *)(*lst)->content;
	int exit_code = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			ms_expand_dquote(lst, &i, env, (t_exp){0, &exit_code});
		else
			i++;
	}
	printf("%s\n", str);

	free(arg);
	ft_lstclear(lst, free);
	free(lst);
	ms_env_clear(env);
	free(env);
}