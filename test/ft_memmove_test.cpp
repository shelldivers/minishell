#include "libft.h"
#include <gtest/gtest.h>

TEST(ft_memmove, ft_memmove_test)
{
	char *src = "hello world";
	char *dst = (char *)malloc(sizeof(char) * 12);
	ft_memmove(dst, src + 2, 12);
	printf("%s\n", dst);
	ASSERT_STREQ(dst, "llo world");
	free(dst);
}