#include "ms_expand.h"
#include "libft.h"
#include <gtest/gtest.h>

void leaks();

TEST(exapnd_quote_test, ms_expand_quote_test)
{
	char *arg = ft_strdup("hello 'world'");
	char *argv[] = {arg, NULL};
	t_list **lst = ms_expand_init(argv);
	int i = 0;
	char *str = (char *)(*lst)->content;
	while (arg[i])
	{
		if (str[i] == '\'')
			ms_expand_quote(lst, *lst, &i, NULL);
		else
			i++;
	}
	printf("%s\n", str);
	EXPECT_STREQ(str, "hello world");
	free(arg);
	ft_lstclear(lst, free);
	free(lst);
	atexit(leaks);
}