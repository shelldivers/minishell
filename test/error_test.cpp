#include <gtest/gtest.h>

TEST(error_test, errno_test) {
	for(int i = 0; i < 135; i++) {
		printf("%d: %s\n", i, strerror(i));
	}
}