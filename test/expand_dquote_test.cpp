#include "ms_expand.h"
#include "libft.h"
#include <gtest/gtest.h>


TEST(exapnd_dquote_test, ms_expand_dquote_test)
{
	char *arg = ft_strdup("\"hello world\"");
	int i = 0;
	while (arg[i])
	{
		if (arg[i] == '\"')
			ms_expand_dquote(arg, &i);
		else
			i++;
	}
	printf("%s\n", arg);
}