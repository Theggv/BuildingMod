#include "gtest/gtest.h"

#include <math/linear/vec2.h>

TEST(Vec2Tests, Test1)
{
    EXPECT_EQ(vec2::One().x, 1);
}