#include "libft.h"
#include "ms_expand.h"
#include <dirent.h>
#include <gtest/gtest.h>

void leaks();

TEST(expand_wildcard, ms_expand_wildcard_test_14)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("!*/$?");
	char *argv[] = {"ls", arg, NULL};

	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);
	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}

// TODO
TEST(expand_wildcard, ms_expand_wildcard_test_13)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("*/$?");
	char *argv[] = {"ls", arg, NULL};

	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);
	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}

TEST(expand_wildcard, ms_expand_wildcard_test_12)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("$*");
	char *argv[] = {"ls", arg, NULL};

	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);
	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}

TEST(expand_wildcard, ms_expand_wildcard_test_11)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("\\/*\\/*/\\/*/*");
	char *argv[] = {"ls", arg, NULL};

	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);
	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}

TEST(expand_wildcard, ms_expand_wildcard_test_10)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("\\/*\\/8*/\\8/8**8/8*?8");
	char *argv[] = {"ls", arg, NULL};

	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);
	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}


TEST(expand_wildcard, ms_wildcard_get_path_remain_test)
{
	char *str;
	char *path;

	path = "./u*/l*/a*";
	str = ms_wildcard_get_last(path);
	ASSERT_STREQ(str, "/l*/a*");
	printf("%s\n", str);
	free(str);

	path = "qwer*qwer";
	str = ms_wildcard_get_last(path);
	ASSERT_STREQ(str, "");
	printf("%s\n", str);
	free(str);

	path = "qwer*qwer/qwer";
	str = ms_wildcard_get_last(path);
	ASSERT_STREQ(str, "/qwer");
	printf("%s\n", str);
	free(str);

	path = "qwer*qwer/qwer/qwer";
	str = ms_wildcard_get_last(path);
	ASSERT_STREQ(str, "/qwer/qwer");
	printf("%s\n", str);
	free(str);
}

TEST(expand_wildcard, ms_expand_wildcard_test_9)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("../../*/*/*.txt");
	char *argv[] = {"ls", arg, NULL};
	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);
	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}

TEST(expand_wildcard, ms_expand_wildcard_test_8)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("../../*/*");
	char *argv[] = {"ls", arg, NULL};
	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);
	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}

TEST(expand_wildcard, ms_expand_wildcard_test_7)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("*/*/*/*");
	char *argv[] = {"ls", arg, NULL};
	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}

	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}

TEST(expand_wildcard, ms_expand_wildcard_test_6)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("./u*/l*/a*");
	char *argv[] = {"ls", arg, NULL};
	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);
	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}

TEST(expand_wildcard, ms_expand_wildcard_test_5)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("./u*/l*");
	char *argv[] = {"ls", arg, NULL};
	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);
	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}

TEST(expand_wildcard, ms_expand_wildcard_test_4)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("./u*/");
	char *argv[] = {"ls", arg, NULL};
	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);
	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}


TEST(expand_wildcard, ms_expand_wildcard_test_3)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("./u*");
	char *argv[] = {"ls", arg, NULL};
	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);
	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}

TEST(expand_wildcard, ms_expand_wildcard_test_2)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("*/*");
	char *argv[] = {"ls", arg, NULL};
	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);

	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);
	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}

TEST(expand_wildcard, ms_expand_wildcard_test)
{
	char *envp[] = {"expand", "hello=world", "SHELL=minishell", NULL};
	t_env **env = ms_env_deserialize(envp);

	char *arg = ft_strdup("*");
	char *argv[] = {"ls", arg, NULL};
	int exit_code = 0;
	char **new_argv = ms_expand(argv, env, &exit_code);
	free(arg);
	ms_env_clear(env);
	free(env);

	leaks();

	if (!new_argv)
		return ;
	int i = 0;
	while (new_argv[i])
	{
		printf("%s\n", new_argv[i]);
		i++;
	}
	printf("i: %d\n", i - 1);

	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}


/**
 * DT_UNKNOWN       0
 * DT_FIFO          1
 * DT_CHR           2
 * DT_DIR           4
 * DT_BLK           6
 * DT_REG           8
 * DT_LNK          10
 * DT_SOCK         12
 * DT_WHT          14
 */
TEST(expand_wildcard, ms_wildcard_get_path)
{
	char *str;
	char *path;

	path = "srcs/test/*";
	str = ms_wildcard_get_path(path);
	ASSERT_STREQ(str, "srcs/test/");
	printf("%s\n", str);
	free(str);

	path = "srcs/test/qwer*";
	str = ms_wildcard_get_path(path);
	ASSERT_STREQ(str, "srcs/test/");
	printf("%s\n", str);
	free(str);

	path = "srcs/test/qwer*/";
	str = ms_wildcard_get_path(path);
	ASSERT_STREQ(str, "srcs/test/");
	printf("%s\n", str);
	free(str);

	path = "/*";
	str = ms_wildcard_get_path(path);
	ASSERT_STREQ(str, "/");
	printf("%s\n", str);
	free(str);

	path = "*";
	str = ms_wildcard_get_path(path);
	ASSERT_STREQ(str, ".");
	printf("%s\n", str);
	free(str);

	path = "*/";
	str = ms_wildcard_get_path(path);
	ASSERT_STREQ(str, ".");
	printf("%s\n", str);
	free(str);

	atexit(leaks);
}

TEST(expand_wildcard, ms_wildcard_get_prefix)
{
	char *str;
	char *path;

	path = "srcs/test/*";
	str = ms_wildcard_get_prefix(path);
	ASSERT_STREQ(str, "");
	printf("%s\n", str);
	free(str);

	path = "srcs/test/qwer*";
	str = ms_wildcard_get_prefix(path);
	ASSERT_STREQ(str, "qwer");
	printf("%s\n", str);
	free(str);

	path = "srcs/test/qwer*/";
	str = ms_wildcard_get_prefix(path);
	ASSERT_STREQ(str, "qwer");
	printf("%s\n", str);
	free(str);

	path = "/*";
	str = ms_wildcard_get_prefix(path);
	ASSERT_STREQ(str, "");
	printf("%s\n", str);
	free(str);

	path = "*";
	str = ms_wildcard_get_prefix(path);
	ASSERT_STREQ(str, "");
	printf("%s\n", str);
	free(str);

	path = "*/";
	str = ms_wildcard_get_prefix(path);
	ASSERT_STREQ(str, "");
	printf("%s\n", str);
	free(str);

	atexit(leaks);
}

TEST(expand_wildcard, ms_wildcard_get_suffix)
{
	char *str;
	char *path;

	path = "srcs/test/*";
	str = ms_wildcard_get_suffix(path);
	ASSERT_STREQ(str, "");
	printf("%s\n", str);
	free(str);

	path = "srcs/test/qwer*awe";
	str = ms_wildcard_get_suffix(path);
	ASSERT_STREQ(str, "awe");
	printf("%s\n", str);
	free(str);

	path = "srcs/test/qwer*/asdf";
	str = ms_wildcard_get_suffix(path);
	ASSERT_STREQ(str, "");
	printf("%s\n", str);
	free(str);

	path = "srcs/test/qwer*asdf/asdf";
	str = ms_wildcard_get_suffix(path);
	ASSERT_STREQ(str, "asdf");
	printf("%s\n", str);
	free(str);

	path = "/*";
	str = ms_wildcard_get_suffix(path);
	ASSERT_STREQ(str, "");
	printf("%s\n", str);
	free(str);

	path = "*";
	str = ms_wildcard_get_suffix(path);
	ASSERT_STREQ(str, "");
	printf("%s\n", str);
	free(str);

	path = "*/";
	str = ms_wildcard_get_suffix(path);
	ASSERT_STREQ(str, "");
	printf("%s\n", str);
	free(str);

	atexit(leaks);
}

TEST(expand_wildcard, opendir_test)
{
	char *pwd = getcwd(NULL, 0);
	DIR *dir = opendir(pwd);
	struct dirent *entry;

	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break;
		if (entry->d_type == DT_DIR)
			printf("dir: %s\n", entry->d_name);
		else
			printf("file: %s\n", entry->d_name);
	}
}
