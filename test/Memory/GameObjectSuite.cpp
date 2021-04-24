#include <pch.h>
#include <boost/test/unit_test.hpp>

#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/BuildingObjects/Objects.h>
#include <game/BuildSystem/GameObjectFactory.h>

class GameObjectMock : public GameObject
{
public:
	void Connect(p_GameObject_t other) override {}
};

BOOST_AUTO_TEST_SUITE(ComponentsSuite)

BOOST_AUTO_TEST_CASE(GameObjectMemoryTest)
{
	// auto object = new GameObjectMock();
	// delete object;
}

BOOST_AUTO_TEST_CASE(FoundationSquareMemoryTest)
{
	auto factory = new GameObjectFactory;
	auto ptr = factory->CreateFoundationSquare(nullptr);
	ObjectManager::Instance().Remove((ptr));

	auto ptr2 = make_shared<int>(1);
	ptr2.reset();

	delete factory;
}

BOOST_AUTO_TEST_CASE(FoundationTriangleMemoryTest)
{
	// auto object = new FoundationTriangle(nullptr);
	// delete object;
}

BOOST_AUTO_TEST_SUITE_END()