#include "minishell.h"
#include "libft.h"
#include <gtest/gtest.h>

TEST(cd, cd_test)
{
	int status = cd(1, (char *[]){"cd", NULL});
	char *cwd = getcwd(NULL, 0);
	printf("[%d] cwd: %s\n", status, cwd);
}

TEST(cd, tilde_test)
{
	int status = cd(2, (char *[]){"cd", "~/projects", NULL});
	char *cwd = getcwd(NULL, 0);
	printf("[%d] cwd: %s\n", status, cwd);
}

TEST(cd, absolute_test)
{
	int status = cd(2, (char *[]){"cd", "/Users/jeongwpa/projects/server", NULL});
	char *cwd = getcwd(NULL, 0);
	printf("[%d] cwd: %s\n", status, cwd);
}

TEST(cd, relative_test)
{
	int status = cd(2, (char *[]){"cd", "../../../server", NULL});
	char *cwd = getcwd(NULL, 0);
	printf("[%d] cwd: %s\n", status, cwd);
}

TEST(cd, perror_test)
{
	chdir("asdf");
	perror("cd");
}

TEST(cd, chdir_test)
{
	char *cwd;
	int status;

	status = chdir("ASDf");
	cwd = getcwd(NULL, 0);
	printf("cwd: %s [%d]\n", cwd, status);
}

TEST(cd, getenv_test)
{
	char *env = getenv("HOME");
	printf("env: %s\n", env);
}

TEST(cd, ft_strrchr_test)
{
	char const *path = "/home/user";
	char *ptr = ft_strrchr(path, '/');
	printf("ptr: %s\n", ptr);
}