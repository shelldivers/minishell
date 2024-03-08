#include "ms_expand.h"
#include "libft.h"
#include <gtest/gtest.h>

void leaks();

TEST(exapnd_env_test, exit_code)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *arg = ft_strdup("hello $?!");
	char *argv[] = {arg, NULL};
	t_list **lst = ms_expand_init(argv);
	int i = 0;
	char **str = (char **)&(*lst)->content;
	int exit_code = 12;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
			ms_expand_env(lst, &i, env, &exit_code);
		else
			i++;
	}
	EXPECT_STREQ("hello 0!", *str);
	printf("%s\n", *str);
	free(arg);
	ft_lstclear(lst, free);
	free(lst);
	ms_env_clear(env);
	printf("env cleared\n");
	free(env);
}

TEST(exapnd_env_test, no_env)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *arg = ft_strdup("hello $test!");
	char *argv[] = {arg, NULL};
	t_list **lst = ms_expand_init(argv);
	int i = 0;
	char **str = (char **)&(*lst)->content;
	int exit_code = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
			ms_expand_env(lst, &i, env, &exit_code);
		else
			i++;
	}
	EXPECT_STREQ("hello !", *str);
	printf("%s\n", *str);
	free(arg);
	ft_lstclear(lst, free);
	free(lst);
	ms_env_clear(env);
	free(env);
	leaks();
}

TEST(exapnd_env_test, ms_expand_env_test)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);
	char *arg = ft_strdup("hello $hello");
	char *argv[] = {arg, NULL};
	t_list **lst = ms_expand_init(argv);
	int i = 0;
	char **str = (char **)&(*lst)->content;
	int exit_code = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
			ms_expand_env(lst, &i, env, &exit_code);
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
	leaks();
}