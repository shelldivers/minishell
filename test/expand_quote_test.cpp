#include "ms_expand.h"
#include "libft.h"
#include <gtest/gtest.h>


TEST(exapnd_quote_test, ms_expand_quote_test)
{
	char *arg = ft_strdup("hello 'world'");
	int i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			ms_expand_quote(arg, &i);
		else
			i++;
	}
	printf("%s\n", arg);
}