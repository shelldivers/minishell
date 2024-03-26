#include "ms_expand.h"
#include <gtest/gtest.h>

using namespace std;

void	leaks();

TEST(ms_opendir_test, ms_opendir_test)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	EXPECT_NE(dir, nullptr);
	closedir(dir);

	dir = opendir("u");
	EXPECT_NE(dir, nullptr);
	closedir(dir);

	dir = opendir("u/lll");
	EXPECT_NE(dir, nullptr);
	closedir(dir);
}

TEST(ms_filename_test, ms_get_pattern_root)
{
	char *pattern;

	pattern = ms_get_pattern("/*");
	printf("pattern: %s\n", pattern);
	EXPECT_STREQ(pattern, "*");
	free(pattern);

	pattern = ms_get_pattern("*");
	printf("pattern: %s\n", pattern);
	EXPECT_STREQ(pattern, "*");
	free(pattern);

	pattern = ms_get_pattern("*asdf");
	printf("pattern: %s\n", pattern);
	EXPECT_STREQ(pattern, "*asdf");
	free(pattern);

	pattern = ms_get_pattern("*asdf/");
	printf("pattern: %s\n", pattern);
	EXPECT_STREQ(pattern, "*asdf/");
	free(pattern);

	pattern = ms_get_pattern("*/asdf");
	printf("pattern: %s\n", pattern);
	EXPECT_STREQ(pattern, "*");
	free(pattern);

	pattern = ms_get_pattern("*/asdf/asdf");
	printf("pattern: %s\n", pattern);
	EXPECT_STREQ(pattern, "*");
	free(pattern);

	pattern = ms_get_pattern("Asdf*asdf/asdf/asdf/asdf*/asdf");
	printf("pattern: %s\n", pattern);
	EXPECT_STREQ(pattern, "Asdf*asdf");
	free(pattern);

	pattern = ms_get_pattern("Asdf*asdf/");
	printf("pattern: %s\n", pattern);
	EXPECT_STREQ(pattern, "Asdf*asdf/");
	free(pattern);

	leaks();
}

TEST(ms_filename_test, ms_get_path_root)
{
	char *path;

	path = ms_get_path("/*");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, "/");
	free(path);

	path = ms_get_path("/asdf*");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, "/");
	free(path);

	path = ms_get_path("/*asdf");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, "/");
	free(path);

	path = ms_get_path("/*/*");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, "/");
	free(path);

	path = ms_get_path("/usr/as*d/*");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, "/usr");
	free(path);

	path = ms_get_path("/usr/asd/*");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, "/usr/asd");
	free(path);

	leaks();
}



TEST(ms_filename_test, ms_get_path_current)
{
	char *path;

	path = ms_get_path("*");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, ".");
	free(path);

	path = ms_get_path("*asdf");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, ".");
	free(path);

	path = ms_get_path("*/");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, ".");
	free(path);

	path = ms_get_path("*/asdf");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, ".");
	free(path);

	path = ms_get_path("asdf*/");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, ".");
	free(path);

	path = ms_get_path("asdf*");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, ".");
	free(path);

	path = ms_get_path("asdf*/asdf");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, ".");
	free(path);

	path = ms_get_path("srcs/*");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, "srcs");
	free(path);

	path = ms_get_path("srcs/*asdf");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, "srcs");
	free(path);


	path = ms_get_path("srcs/*/");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, "srcs");
	free(path);

	path = ms_get_path("srcs/asdf*");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, "srcs");
	free(path);

	path = ms_get_path("srcs/asdf*/");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, "srcs");
	free(path);

	path = ms_get_path("srcs/asdf/*");
	printf("path: %s\n", path);
	EXPECT_STREQ(path, "srcs/asdf");
	free(path);

	leaks();
}



