#include <pch.h>
#include <boost/test/unit_test.hpp>

#include <Utility/Transform.h>

BOOST_AUTO_TEST_SUITE(TransformTests)

BOOST_AUTO_TEST_CASE(TransformCreateSuite)
{
	auto transform = new Transform;
	delete transform;
}

BOOST_AUTO_TEST_CASE(TransformGetPosAndRot)
{
	auto transform = new Transform;
	auto pos = transform->GetPosition();
	auto rot = transform->GetRotation();

	if (pos == nullptr)
		BOOST_FAIL("Position is null");

	if (rot == nullptr)
		BOOST_FAIL("Rotation is null");

	delete transform;
}

BOOST_AUTO_TEST_SUITE_END()
