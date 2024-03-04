#include "libft.h"
#include "ms_builtin.h"
#include "minishell.h"
#include "ms_env.h"
#include <gtest/gtest.h>

TEST(cd, cd_test)
{
	// given
	int argc = 1;
	char *argv[] = {"cd", NULL};
	char *pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	char *home = ft_strjoin("HOME=", getenv("HOME"));
	char *envp[] = {pwd, home, NULL};
	t_env **env = ms_env_deserialize(envp);
	char *old_pwd = ms_getenv(*env, "PWD");

	// when
	int status = ms_cd(argc, argv, env);

	// then
	EXPECT_EQ(status, 0);
	EXPECT_STREQ(getcwd(NULL, 0), ms_getenv(*env, "PWD"));
	EXPECT_STREQ(old_pwd, ms_getenv(*env, "OLDPWD"));
}

TEST(cd, tilde_test)
{
	// given
	int argc = 2;
	char *argv[] = {"cd", "~", NULL};
	char *pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	char *home = ft_strjoin("HOME=", getenv("HOME"));
	char *envp[] = {pwd, home, NULL};
	t_env **env = ms_env_deserialize(envp);
	char *old_pwd = ft_strdup(ms_getenv(*env, "PWD"));

	// when
	int status = ms_cd(argc, argv, env);

	// then
	EXPECT_EQ(status, 0);
	EXPECT_STREQ(getcwd(NULL, 0), ms_getenv(*env, "PWD"));
	EXPECT_STREQ(old_pwd, ms_getenv(*env, "OLDPWD"));
}

TEST(cd, tilde_with_path_test)
{
	int argc = 2;
	char *argv[] = {"cd", "~/projects/minishell", NULL};
	char *pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	char *home = ft_strjoin("HOME=", getenv("HOME"));
	char *envp[] = {pwd, home, NULL};
	t_env **env = ms_env_deserialize(envp);
	char *old_pwd = ft_strdup(ms_getenv(*env, "PWD"));

	int status = ms_cd(argc, argv, env);

	EXPECT_EQ(status, 0);
	EXPECT_STREQ(getcwd(NULL, 0), ms_getenv(*env, "PWD"));
	EXPECT_STREQ(old_pwd, ms_getenv(*env, "OLDPWD"));
}

TEST(cd, absolute_test)
{
	int argc = 2;
	char *argv[] = {"cd", "/Users/jeongwpa/projects", NULL};
	char *pwd = ft_strjoin("PATH=", getcwd(NULL, 0));
	char *home = ft_strjoin("HOME=", getenv("HOME"));
	char *envp[] = {pwd, home, NULL};

	t_env **env = ms_env_deserialize(envp);
	int status = ms_cd(argc, argv, env);
	EXPECT_EQ(status, 0);
	char *cwd = getcwd(NULL, 0);
	printf("[%d] cwd: %s\n", status, cwd);
}

TEST(cd, relative_test)
{
	char *root = "/Users/jeongwpa/projects/minishell/cmake-build-debug/test";
	chdir(root);
	int argc = 2;
	char *argv[] = {"cd", "../../../minishell", NULL};
	char *pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	char *home = ft_strjoin("HOME=", getenv("HOME"));
	char *envp[] = {pwd, home, NULL};
	t_env **env = ms_env_deserialize(envp);
	char *old_pwd = ft_strdup(ms_getenv(*env, "PWD"));

	int status = ms_cd(argc, argv, env);

	EXPECT_EQ(status, 0);
	EXPECT_STREQ(getcwd(NULL, 0), ms_getenv(*env, "PWD"));
	EXPECT_STREQ(old_pwd, ms_getenv(*env, "OLDPWD"));
}