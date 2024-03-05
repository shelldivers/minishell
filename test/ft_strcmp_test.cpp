#include "minishell.h"
#include "libft.h"
#include <gtest/gtest.h>

TEST(ft_strcmp, basic_test)
{
	char *s1;
	char *s2;
	s1 = "Hello";
	s2 = "Hello";
	ASSERT_EQ(ft_strcmp(s1, s2), 0);

	s1 = "Hello";
	s2 = "Hello!";
	ASSERT_EQ(ft_strcmp(s1, s2), -33);

	s1 = "Hello!";
	s2 = "Hello";
	ASSERT_EQ(ft_strcmp(s1, s2), 33);

	s1 = "Hello";
	s2 = "World";
	ASSERT_EQ(ft_strcmp(s1, s2), -15);

	s1 = "World";
	s2 = "Hello";
	ASSERT_EQ(ft_strcmp(s1, s2), 15);

	s1 = "Hello";
	s2 = "";
	ASSERT_EQ(ft_strcmp(s1, s2), 72);

	s1 = "";
	s2 = "Hello";
	ASSERT_EQ(ft_strcmp(s1, s2), -72);

	s1 = "";
	s2 = "";
	ASSERT_EQ(ft_strcmp(s1, s2), 0);

	s1 = "Hello";
	s2 = "Hello";
	ASSERT_EQ(ft_strcmp(s1, s2), 0);
}