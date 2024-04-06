#include "libft.h"
#include "ms_env.h"
#include "ms_expand.h"
#include <gtest/gtest.h>

using namespace std;

TEST(ms_expand_param, ms_expand_param)
{
	char *argv[3];
	char *envp[] = {"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki", "PWD=/Users/jeongwpa", "SHLVL=1", "HOME=/Users/jeongwpa", "LOGNAME=jeongwpa", "USER=jeongwpa", "TERM=xterm-256color", "ITERM_PROFILE=Default", "ITERM_SESSION_ID=w0t0p0:0E3E3E3E-3E3E-3E3E-3E3E-3E3E3E3E3E3E", "COLORTERM=truecolor", "XPC_FLAGS=0x0", "XPC_SERVICE_NAME=0", NULL};
	t_env **env;
	int status;
	char **result;

	status = 0;
	env = ms_env_deserialize(envp);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("$?");
	argv[2] = NULL;

	result = ms_expand_params(argv, status, *env);
	for(int i = 0; result[i]; i++)
		cout << "result: " << result[i] << endl;
	EXPECT_NE(result, nullptr);

	for(int i = 0; argv[i]; i++)
		free(argv[i]);
	ms_env_clear(env);
	free(env);
}