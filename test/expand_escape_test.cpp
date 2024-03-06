#include "ms_expand.h"
#include "libft.h"
#include <gtest/gtest.h>

void leaks();

TEST(exapnd_escape_test, ms_expand_escape_test)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *arg = ft_strdup("h\"el\\lo world\'");
	char *argv[] = {arg, NULL};
	t_list **lst = ms_expand_init(argv);
	int i = 0;
	while (arg[i])
	{
		if (arg[i] == '\"')
			ms_expand_dquote(lst, lst, &i, env);
		else
			i++;
	}
	printf("%s\n", arg);
	free(arg);
	ft_lstclear(lst, free);
	free(lst);
	ms_env_clear(env);
	free(env);
	atexit(leaks);
}

TEST(exapnd_escape_test, ms_expand_escape)
{
	char *arg = ft_strdup("\\\\ \\\\ \\\\ \\\\");
	char *argv[] = {arg, NULL};
	t_list **lst = ms_expand_init(argv);
	int i = 0;
	char *str = (char *)(*lst)->content;
	while (str[i])
	{
		if (str[i] == '\\')
			ms_expand_escape(lst, lst, &i, NULL);
		else
			i++;
	}
	printf("%s\n", str);
	free(arg);
	ft_lstclear(lst, free);
	free(lst);
	atexit(leaks);
}
