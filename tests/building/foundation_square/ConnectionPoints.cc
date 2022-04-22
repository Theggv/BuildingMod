#include <gtest/gtest.h>
#include <building/foundation_square/ConnectionPoints.h>
#include <building/constants.h>

typedef FoundationSquareConnectionPoints ConnPoint;

TEST(FoundationSquareConnPointsTests, IsEqual)
{
	vec3 origin(0, 0, 0);
	double angle = 90;

	auto points = std::make_unique<ConnectionPoints>();

	EXPECT_EQ(points->GetAbsolute(ConnPoint::LEFT, origin, angle).pos, vec3(0, -UNIT_SIZE / 2) );
	EXPECT_EQ(points->GetAbsolute(ConnPoint::UP, origin, angle).pos, vec3(-UNIT_SIZE / 2, 0) );
	EXPECT_EQ(points->GetAbsolute(ConnPoint::RIGHT, origin, angle).pos, vec3(0, UNIT_SIZE / 2));
	EXPECT_EQ(points->GetAbsolute(ConnPoint::DOWN, origin, angle).pos, vec3(UNIT_SIZE / 2, 0));
}