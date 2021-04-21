#include <pch.h>
#include <boost/test/unit_test.hpp>

#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

BOOST_AUTO_TEST_SUITE(GeometryTests)

BOOST_AUTO_TEST_CASE(GeometryTriangleTriangleInterTest)
{
    auto triangle1 = new Shape({vec2(3, 1), vec2(6, 1), vec2(3, 5)});
    auto triangle2 = new Shape({vec2(4, 2), vec2(6, 6), vec2(8, 2)});

    auto inter = triangle1->IsIntersect(*triangle2);

    BOOST_CHECK_EQUAL(inter, true);

    delete triangle1;
    delete triangle2;
}

BOOST_AUTO_TEST_CASE(GeometryTriangleTriangleInterTest2)
{
    auto triangle1 = new Shape({vec2(1005, 1069), vec2(905, 1027), vec2(919, 1134)});
    auto triangle2 = new Shape({vec2(841, 1035), vec2(855, 1143), vec2(941, 1077)});

    auto inter = triangle1->IsIntersect(*triangle2);

    BOOST_CHECK_EQUAL(inter, true);

    delete triangle1;
    delete triangle2;
}

BOOST_AUTO_TEST_CASE(GeometryTriangleRectInterTest)
{
    auto triangle1 = new Shape({vec2(1, 2), vec2(1, 3), vec2(2, 2)});
    auto rect1 = new Shape({vec2(0, 0), vec2(0, 3), vec2(3, 3), vec2(3, 0)});

    auto inter = triangle1->IsIntersect(*rect1);

    BOOST_CHECK_EQUAL(inter, true);

    delete triangle1;
    delete rect1;
}

BOOST_AUTO_TEST_CASE(GeometryTriangleRectInterTest2)
{
    auto triangle1 = new Shape({vec2(0, 0), vec2(5, -1), vec2(3, 5)});
    auto rect1 = new Shape({vec2(6, 0), vec2(10, 0), vec2(10, 4), vec2(6, 4)});

    auto inter = triangle1->IsIntersect(*rect1);

    BOOST_CHECK_EQUAL(inter, false);

    delete triangle1;
    delete rect1;
}

BOOST_AUTO_TEST_CASE(GeometryRectRectInterTest)
{
    auto rect1 = new Shape({vec2(0, 0), vec2(0, 3), vec2(3, 3), vec2(3, 0)});
    auto rect2 = new Shape({vec2(2, 2), vec2(2, 5), vec2(5, 5), vec2(5, 2)});

    auto inter = rect1->IsIntersect(*rect2);

    BOOST_CHECK_EQUAL(inter, true);

    delete rect1;
    delete rect2;
}

BOOST_AUTO_TEST_CASE(RayIntersectionTest)
{
    auto start = vec3(-250, -250, 0);
    auto end = vec3(0, 0, 0);
    auto _ray = new ray(start, end - start, 500);
    auto aabb = new aabb2(vec2(0, 0), vec2(128, 128));

    auto inter = aabb->RayIntersection(*_ray);

    BOOST_CHECK_EQUAL(inter, true);

    delete _ray;
    delete aabb;
}

BOOST_AUTO_TEST_CASE(GetAreaByIndexTest)
{
    auto point = vec3(550, -390, 0);

    auto index = ObjectManager::Instance().CalculateWorldPosition(point.x, point.y);
    auto aabb = ObjectManager::Instance().GetAreaByIndex(index);

    auto isXinsideInterval = point.x >= aabb.GetMins().x && point.x <= aabb.GetMaxs().x;
    auto isYinsideInterval = point.y >= aabb.GetMins().y && point.y <= aabb.GetMaxs().y;

    BOOST_CHECK_EQUAL(isXinsideInterval, true);
    BOOST_CHECK_EQUAL(isYinsideInterval, true);
}

BOOST_AUTO_TEST_CASE(RayIntersectionTest2)
{
    auto start = vec3(-250, -250, 0);
    auto end = vec3(0, 0, 0);
    auto _ray = new ray(start, end - start, 500);

    auto index = ObjectManager::Instance().CalculateWorldPosition(start.x, start.y);
    auto aabb = ObjectManager::Instance().GetAreaByIndex(index);

    auto inter = aabb.RayIntersection(*_ray);

    BOOST_CHECK_EQUAL(inter, true);

    delete _ray;
}

BOOST_AUTO_TEST_SUITE_END()