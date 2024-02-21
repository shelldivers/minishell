#include "libft.h"
#include "minishell.h"
#include <gtest/gtest.h>

TEST(env_test, deserialize)
{
	char **envp = (char *[]){"PWD=/Users/jeongwpa", "SHLVL=1", "LOGNAME=jeongwpa", "USER=jeongwpa", "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/go/bin:/usr/local/munki", "HOME=/Users/jeongwpa", "TERM_PROGRAM=Apple_Terminal", "TERM=xterm-256color", "SHELL=/bin/zsh", "TMPDIR=/var/folders/3_/3", NULL};
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

TEST(env_test, setenv)
{
	t_env *env = NULL;
	ms_setenv(&env, "PWD", "/Users/jeongwpa");
	ms_setenv(&env, "SHLVL", "1");
	ms_setenv(&env, "LOGNAME", "jeongwpa");
	ms_setenv(&env, "USER", "jeongwpa");
	ms_setenv(&env, "PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/go/bin:/usr/local/munki");
	ms_setenv(&env, "HOME", "/Users/jeongwpa");
	ms_setenv(&env, "TERM_PROGRAM", "Apple_Terminal");
	ms_setenv(&env, "TERM", "xterm-256color");
	ms_setenv(&env, "SHELL", "/bin/zsh");
	ms_setenv(&env, "TMPDIR", "/var/folders/3_/3");
	ms_setenv(&env, "TEST", "Hello World!");
	ms_setenv(&env, "TEST", "Goodbye World!");
	t_env *node = env;
	while (node)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	ms_env_clear(&env);
}

TEST(env_test, getenv)
{
	t_env *env = NULL;
	ms_setenv(&env, "PWD", "/Users/jeongwpa");
	ms_setenv(&env, "SHLVL", "1");
	ms_setenv(&env, "LOGNAME", "jeongwpa");

	char *value = ms_getenv(env, "PWD");
	printf("PWD=%s\n", value);
	value = ms_getenv(env, "SHLVL");
	printf("SHLVL=%s\n", value);
	value = ms_getenv(env, "LOGNAME");
	printf("LOGNAME=%s\n", value);
	ms_env_clear(&env);
}