#include <gtest/gtest.h>

TEST(test_test, self_test)
{
    const auto x = true;
    ASSERT_EQ(x, true);
}
