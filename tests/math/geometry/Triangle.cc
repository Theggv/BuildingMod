#include <gtest/gtest.h>
#include <math/linear/vec3.h>
#include <math/geometry/Triangle.h>

TEST(TriangleTests, IsEqual)
{
	EXPECT_EQ(Triangle(vec3(0, 0), vec3(1, 0), vec3(0, 1)) ==
		Triangle(vec3(0, 0), vec3(1, 0), vec3(0, 1)), true);
}