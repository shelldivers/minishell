#include "minishell.h"
#include "ms_builtin.h"
#include <gtest/gtest.h>

TEST(echo, basic_case)
{
	// open stream
	FILE *stdout_backup = freopen(NULL, "w", stdout);
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	FILE *string_stream = fmemopen(buffer, sizeof(buffer), "w");
	if (string_stream == NULL)
	{
		fprintf(stderr, "스트림을 열 수 없습니다.\n");
		exit(1);
	}
	stdout = string_stream;

	// given
	char *argv[] = {"echo", "Hello", "World", NULL};
	int argc = 3;

	// when
	ms_echo(argc, argv, NULL);

	// close stream
	fclose(string_stream);
	stdout = stdout_backup;

	// then
	EXPECT_STREQ(buffer, "Hello World\n");	// newline
}

TEST(echo, with_option)
{
	// open stream
	FILE *stdout_backup = freopen(NULL, "w", stdout);
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	FILE *string_stream = fmemopen(buffer, sizeof(buffer), "w");
	if (string_stream == NULL)
	{
		fprintf(stderr, "스트림을 열 수 없습니다.\n");
		exit(1);
	}
	stdout = string_stream;

	// given
	char *argv[] = {"echo", "-n", "Hello", "World!", NULL};
	int argc = 4;

	// when
	ms_echo(argc, argv, NULL);

	// close stream
	fclose(string_stream);
	stdout = stdout_backup;

	// then
	EXPECT_STREQ(buffer, "Hello World!");	// NO newline
}

TEST(echo, invalid_option)
{
	// open stream
	FILE *stdout_backup = freopen(NULL, "w", stdout);
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	FILE *string_stream = fmemopen(buffer, sizeof(buffer), "w");
	if (string_stream == NULL)
	{
		fprintf(stderr, "스트림을 열 수 없습니다.\n");
		exit(1);
	}
	stdout = string_stream;

	// given
	char *argv[] = {"echo", "-e", "Hello", "World!", NULL};
	int argc = 4;

	// when
	ms_echo(argc, argv, NULL);

	// close stream
	fclose(string_stream);
	stdout = stdout_backup;

	// then
	EXPECT_STREQ(buffer, "-e Hello World!\n");
}

TEST(echo, no_argv)
{
	// open stream
	FILE *stdout_backup = freopen(NULL, "w", stdout);
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	FILE *string_stream = fmemopen(buffer, sizeof(buffer), "w");
	if (string_stream == NULL)
	{
		fprintf(stderr, "스트림을 열 수 없습니다.\n");
		exit(1);
	}
	stdout = string_stream;

	// given
	char *argv[] = {"echo", NULL};
	int argc = 1;

	// when
	ms_echo(argc, argv, NULL);

	// close stream
	fclose(string_stream);
	stdout = stdout_backup;

	// then
	EXPECT_STREQ(buffer, "\n");
}

TEST(echo, no_argv_n_option)
{
	// open stream
	FILE *stdout_backup = freopen(NULL, "w", stdout);
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	FILE *string_stream = fmemopen(buffer, sizeof(buffer), "w");
	if (string_stream == NULL)
	{
		fprintf(stderr, "스트림을 열 수 없습니다.\n");
		exit(1);
	}
	stdout = string_stream;

	// given
	char *argv[] = {"echo", "-n",NULL};
	int argc = 2;

	// when
	ms_echo(argc, argv, NULL);

	// close stream
	fclose(string_stream);
	stdout = stdout_backup;

	// then
	EXPECT_STREQ(buffer, "");
}