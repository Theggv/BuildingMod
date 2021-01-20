#define BOOST_TEST_MODULE Geometry

#include <pch.h>
#include <boost/test/included/unit_test.hpp>
#include <game/Geometry/Shape.h>
#include <game/Geometry/vec2.h>

BOOST_AUTO_TEST_CASE(GeometryTriangleTriangleInterTest)
{
    auto triangle1 = new Shape({vec2(0, 0), vec2(4, 1), vec2(3, 2)});
    auto triangle2 = new Shape({vec2(1, 2), vec2(1, 3), vec2(2, 2)});

    auto inter = triangle1->IsIntersect(*triangle2);

    BOOST_CHECK_EQUAL(inter, true);
}

BOOST_AUTO_TEST_CASE(GeometryTriangleRectInterTest)
{
    auto triangle1 = new Shape({vec2(1, 2), vec2(1, 3), vec2(2, 2)});
    auto rect1 = new Shape({vec2(0, 0), vec2(0, 3), vec2(3, 3), vec2(3, 0)});

    auto inter = triangle1->IsIntersect(*rect1);

    BOOST_CHECK_EQUAL(inter, true);
}

BOOST_AUTO_TEST_CASE(GeometryRectRectInterTest)
{
    auto rect1 = new Shape({vec2(0, 0), vec2(0, 3), vec2(3, 3), vec2(3, 0)});
    auto rect2 = new Shape({vec2(2, 2), vec2(2, 5), vec2(5, 5), vec2(5, 2)});

    auto inter = rect1->IsIntersect(*rect2);

    BOOST_CHECK_EQUAL(inter, true);
}
