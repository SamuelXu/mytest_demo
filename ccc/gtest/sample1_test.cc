#include "gtest/gtest.h"
#include "sample1.h"
#include <limits.h>

TEST(IsPrimeTest, Negative) {
	EXPECT_FALSE(IsPrime(-1));
	EXPECT_FALSE(IsPrime(-2));
	EXPECT_FALSE(IsPrime(INT_MIN));
}

TEST(IsPrimeTest, Trivial) {
	EXPECT_FALSE(IsPrime(0));
	EXPECT_FALSE(IsPrime(1));
	EXPECT_TRUE(IsPrime(2));
	EXPECT_TRUE(IsPrime(3));
}

TEST(IsPrimeTest, Positive) {
	EXPECT_FALSE(IsPrime(4));
	EXPECT_TRUE(IsPrime(5));
	EXPECT_FALSE(IsPrime(9));
	EXPECT_TRUE(IsPrime(23));
	EXPECT_FALSE(IsPrime(25));
}

