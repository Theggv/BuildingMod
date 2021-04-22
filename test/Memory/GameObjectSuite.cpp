#include <pch.h>
#include <boost/test/unit_test.hpp>

#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/BuildingObjects/Objects.h>

class GameObjectMock : public GameObject
{
public:
	void Connect(GameObject *other) override {}
};

BOOST_AUTO_TEST_SUITE(ComponentsSuite)

BOOST_AUTO_TEST_CASE(GameObjectMemoryTest)
{
	auto object = new GameObjectMock();
	delete object;
}

BOOST_AUTO_TEST_CASE(FoundationSquareMemoryTest)
{
	auto object = new FoundationSquare(nullptr);
	delete object;
}

BOOST_AUTO_TEST_CASE(FoundationTriangleMemoryTest)
{
	auto object = new FoundationTriangle(nullptr);
	delete object;
}

BOOST_AUTO_TEST_SUITE_END()