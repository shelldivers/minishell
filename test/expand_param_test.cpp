#include "libft.h"
#include "ms_env.h"
#include "ms_error.h"
#include "ms_expand.h"
#include <gtest/gtest.h>

using namespace std;

void	leaks()
{
	system("leaks minishell_test");
}

TEST(ms_expand_param, ms_status_expansion)
{
	char *str;
	char *pos;
	int status;
	char *result;

	str = "echo $?";
	pos = ft_strchr(str, '$');
	status = 0;
	result = ms_status_expansion(str, pos, status);
	cout << "result: " << result << endl;
	EXPECT_STREQ(result, "echo 0");
	free(result);
}

TEST(ms_expand_param, ms_expand_param)
{
	char *argv[3];
	char *envp[] = {"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki", "PWD=/Users/jeongwpa", "SHLVL=1", "HOME=/Users/jeongwpa", "LOGNAME=jeongwpa", "USER=jeongwpa", "TERM=xterm-256color", "ITERM_PROFILE=Default", "ITERM_SESSION_ID=w0t0p0:0E3E3E3E-3E3E-3E3E-3E3E-3E3E3E3E3E3E", "COLORTERM=truecolor", "XPC_FLAGS=0x0", "XPC_SERVICE_NAME=0", NULL};
	t_env **env;
	int status;
	t_bool result;

	status = 0;
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("$HOME $TERM$? $?$PWD");
	argv[2] = NULL;
	result = ms_expand_param(argv, *env, status);
	cout << "result: " << argv[1] << endl;
	EXPECT_EQ(result, TRUE);
	leaks();
}

TEST(ms_expand_param, ms_expand_param_status)
{
	char *argv[3];
	char *envp[] = {"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki", "PWD=/Users/jeongwpa", "SHLVL=1", "HOME=/Users/jeongwpa", "LOGNAME=jeongwpa", "USER=jeongwpa", "TERM=xterm-256color", "ITERM_PROFILE=Default", "ITERM_SESSION_ID=w0t0p0:0E3E3E3E-3E3E-3E3E-3E3E-3E3E3E3E3E3E", "COLORTERM=truecolor", "XPC_FLAGS=0x0", "XPC_SERVICE_NAME=0", NULL};
	t_env **env;
	int status;
	t_bool result;

	status = 0;
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("$?$?$? $?");
	argv[2] = NULL;
	result = ms_expand_param(argv, *env, status);
	cout << "result: " << argv[1] << endl;
	EXPECT_EQ(result, TRUE);
	leaks();
}