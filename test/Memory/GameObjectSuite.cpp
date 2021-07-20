#include <pch.h>
#include <boost/test/unit_test.hpp>

#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/BuildingObjects/Objects.h>
#include <game/BuildSystem/GameObjectFactory.h>

BOOST_AUTO_TEST_SUITE(ComponentsSuite)

BOOST_AUTO_TEST_CASE(WallFullMemoryTest)
{
	auto factory = new GameObjectFactory;
	auto ptr = factory->CreateWall(nullptr);

	ObjectManager::Instance().Remove((ptr));

	delete factory;
}

BOOST_AUTO_TEST_CASE(FoundationSquareMemoryTest)
{
	auto factory = new GameObjectFactory;
	auto ptr = factory->CreateFoundationSquare(nullptr);

	ObjectManager::Instance().Remove((ptr));

	delete factory;
}

BOOST_AUTO_TEST_CASE(FoundationTriangleMemoryTest)
{
	auto factory = new GameObjectFactory;
	auto ptr = factory->CreateFoundationTriangle(nullptr);

	ObjectManager::Instance().Remove((ptr));

	delete factory;
}

BOOST_AUTO_TEST_SUITE_END()