#include "libft.h"
#include "minishell.h"
#include <gtest/gtest.h>

TEST(pwd, basic)
{
	// stdout backup
	FILE *stdout_backup = freopen(NULL, "w", stdout);

	// open stream
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	FILE *string_stream = fmemopen(buffer, sizeof(buffer), "w");
	if (string_stream == NULL)
	{
		fprintf(stderr, "스트림을 열 수 없습니다.\n");
		exit(1);
	}
	stdout = string_stream;

	// when
	int argc = 1;
	char *argv[] = {"pwd"};

	int status = ms_pwd(argc, argv);

	buffer[ft_strlen(buffer) - 1] = '\0';	// remove newline

	// close stream
	fclose(string_stream);
	stdout = stdout_backup;

	// then
	EXPECT_EQ(status, 0);
	EXPECT_STREQ(buffer, getcwd(NULL, 0));
}

TEST(pwd, too_many_args) {
	// stdout backup
	FILE *stdout_backup = freopen(NULL, "w", stdout);

	// open stream
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	FILE *string_stream = fmemopen(buffer, sizeof(buffer), "w");
	if (string_stream == NULL)
	{
		fprintf(stderr, "스트림을 열 수 없습니다.\n");
		exit(1);
	}
	stdout = string_stream;

	int	argc = 2;
	char *argv[] = {"pwd", "test"};

	int status = ms_pwd(argc, argv);

	buffer[ft_strlen(buffer) - 1] = '\0';	// remove newline

	// close stream
	fclose(string_stream);
	stdout = stdout_backup;

	// then
	EXPECT_EQ(status, 0);
	EXPECT_STREQ(buffer, getcwd(NULL, 0));
}
