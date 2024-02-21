#include "minishell.h"
#include "libft.h"
#include <gtest/gtest.h>

TEST(env_test, deserialize)
{
	char **envp = (char *[]){
		"PWD=/Users/jeongwpa",
		"SHLVL=1",
		"LOGNAME=jeongwpa",
		"USER=jeongwpa",
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/go/bin:/usr/local/munki",
		"HOME=/Users/jeongwpa",
		"TERM_PROGRAM=Apple_Terminal",
		"TERM=xterm-256color",
		"SHELL=/bin/zsh",
		"TMPDIR=/var/folders/3_/3",
		NULL};
	t_env **head = ms_env_deserialize(envp);
	t_env *node = *head;
	while (node)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	ms_env_clear(head);
}

TEST(env_test, serialize)
{
	t_env *env = (t_env *)malloc(sizeof(t_env));
	env->key = ft_strdup("PWD");
	env->value = ft_strdup("/Users/jeongwpa");
	env->next = (t_env *)malloc(sizeof(t_env));
	env->next->key = ft_strdup("SHLVL");
	env->next->value = ft_strdup("1");
	env->next->next = NULL;
	char **envp = ms_env_serialize(env);
	int i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	while (i >= 0)
	{
		free(envp[i]);
		i--;
	}
	free(envp);
	ms_env_clear(&env);
}