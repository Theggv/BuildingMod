#include <pch.h>
#include <boost/test/unit_test.hpp>

#include <Utility/Transform.h>

BOOST_AUTO_TEST_SUITE(UtilitySuite)

BOOST_AUTO_TEST_CASE(TransformMemoryTest)
{
	auto transform = new Transform();
	delete transform;
}

BOOST_AUTO_TEST_SUITE_END()