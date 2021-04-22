#include <pch.h>
#include <boost/test/unit_test.hpp>
#include "mocks.h"

#include <game/BuildSystem/BuildingObjects/Objects.h>
#include <game/BuildSystem/BuildingObjects/Foundations/FoundationSquare/StabilityComponent.h>
#include <game/BuildSystem/BuildingObjects/Walls/WallFull/StabilityComponent.h>
#include <game/BuildSystem/ConnectionManager.h>


BOOST_AUTO_TEST_SUITE(ConnectionSuite)

BOOST_AUTO_TEST_CASE(ConnectionManagerTest)
{
	auto object1 = InitObject(new FoundationSquareMock(nullptr));
	auto object2 = InitObject(new FoundationSquareMock(nullptr));

	BOOST_CHECK(ConnectionManager::Instance().AddLinkParentChild(object1, object2) == true);

	BOOST_CHECK(ConnectionManager::Instance().AddLinkParentChild(object1, object2) == false);
	BOOST_CHECK(ConnectionManager::Instance().AddLinkParentChild(object2, object1) == false);
	BOOST_CHECK(ConnectionManager::Instance().AddLinkIndependent(object1, object2) == false);
	BOOST_CHECK(ConnectionManager::Instance().AddLinkAdditional(object1, object2) == false);

	auto object3 = InitObject(new FoundationSquareMock(nullptr));
	auto object4 = InitObject(new FoundationSquareMock(nullptr));

	BOOST_CHECK(ConnectionManager::Instance().AddLinkIndependent(object1, object3) == true);
	BOOST_CHECK(ConnectionManager::Instance().AddLinkAdditional(object1, object4) == true);

	auto links = ConnectionManager::Instance().GetAllLinks(object1);

	BOOST_CHECK_EQUAL(links.size(), 3);

	delete object1;
	delete object2;
	delete object3;
	delete object4;

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_CASE(BasicConnectionTest)
{
	auto foundation1 = InitObject(new FoundationSquareMock(nullptr));
	MakeSolid(foundation1);

	auto foundation2 = InitObject(new FoundationSquareMock(nullptr));
	foundation2->GetTransform()->GetPosition()->x(FoundationSquare::m_ModelSize);
	MakeSolid(foundation2);

	auto links1 = ConnectionManager::Instance().GetAllLinks(foundation1);
	auto links2 = ConnectionManager::Instance().GetAllLinks(foundation2);

	BOOST_CHECK_EQUAL(links1.size(), 1);
	BOOST_CHECK_EQUAL(links2.size(), 1);

	delete foundation1;
	delete foundation2;

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_CASE(ComplexConnectionTest)
{
	auto foundation1 = InitObject(new FoundationSquareMock(nullptr));
	MakeSolid(foundation1);

	auto foundation2 = InitObject(new FoundationSquareMock(nullptr));
	foundation2->GetTransform()->GetPosition()->x(FoundationSquare::m_ModelSize);
	MakeSolid(foundation2);

	auto wall1 = InitObject(new WallFullMock(nullptr));
	wall1->GetTransform()->GetPosition()->x(FoundationSquare::m_ModelSize / 2);
	MakeSolid(wall1);

	auto wall2 = InitObject(new WallFullMock(nullptr));
	wall2->GetTransform()->GetPosition()->y(FoundationSquare::m_ModelSize / 2);
	wall2->GetTransform()->GetRotation()->y(90);
	MakeSolid(wall2);

	auto links1 = ConnectionManager::Instance().GetAllLinks(foundation1);
	auto links2 = ConnectionManager::Instance().GetAllLinks(foundation2);

	BOOST_CHECK_EQUAL(links1.size(), 3);
	BOOST_CHECK_EQUAL(links2.size(), 2);

	auto links3 = ConnectionManager::Instance().GetAdditionals(wall1);
	auto links4 = ConnectionManager::Instance().GetParents(wall1);

	BOOST_CHECK_EQUAL(links3.size(), 1);
	BOOST_CHECK_EQUAL(links4.size(), 2);

	delete foundation1;
	delete foundation2;

	delete wall1;
	delete wall2;

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_CASE(BasicAdditionalConnectionTest)
{
	auto wall1 = InitObject(new WallFullMock(nullptr));
	MakeSolid(wall1);

	// Стена изначально расположена параллельно оси y
	auto wall2 = InitObject(new WallFullMock(nullptr));
	wall2->GetTransform()->GetPosition()->y(FoundationSquare::m_ModelSize);
	MakeSolid(wall2);

	auto wall1Links = ConnectionManager::Instance().GetAdditionals(wall1);
	auto wall2Links = ConnectionManager::Instance().GetAdditionals(wall2);

	BOOST_CHECK_EQUAL(wall1Links.size(), 1);
	BOOST_CHECK_EQUAL(wall2Links.size(), 1);

	delete wall1;
	delete wall2;

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_CASE(BasicAdditionalConnectionTest2)
{
	auto wall1 = InitObject(new WallFullMock(nullptr));
	wall1->GetTransform()->GetRotation()->y(90); // Параллельно x
	MakeSolid(wall1);

	// Стена изначально расположена параллельно оси y
	auto wall2 = InitObject(new WallFullMock(nullptr));
	wall2->GetTransform()->GetRotation()->y(90); // Параллельно x
	wall2->GetTransform()->GetPosition()->x(FoundationSquare::m_ModelSize);
	MakeSolid(wall2);

	auto wall1Links = ConnectionManager::Instance().GetAdditionals(wall1);
	auto wall2Links = ConnectionManager::Instance().GetAdditionals(wall2);

	BOOST_CHECK_EQUAL(wall1Links.size(), 1);
	BOOST_CHECK_EQUAL(wall2Links.size(), 1);

	delete wall1;
	delete wall2;

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_CASE(BasicAdditionalConnectionTest3)
{
	auto wall1 = InitObject(new WallFullMock(nullptr));
	wall1->GetTransform()->GetRotation()->y(90); // Параллельно x
	MakeSolid(wall1);

	// Стена изначально расположена параллельно оси y
	auto wall2 = InitObject(new WallFullMock(nullptr));
	wall2->GetTransform()->GetRotation()->y(90); // Параллельно x
	wall2->GetTransform()->GetPosition()->y(FoundationSquare::m_ModelSize);
	MakeSolid(wall2);

	auto wall1Links = ConnectionManager::Instance().GetAdditionals(wall1);
	auto wall2Links = ConnectionManager::Instance().GetAdditionals(wall2);

	BOOST_CHECK_EQUAL(wall1Links.size(), 0);
	BOOST_CHECK_EQUAL(wall2Links.size(), 0);

	delete wall1;
	delete wall2;

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_CASE(BasicAdditionalConnectionTest4)
{
	auto wall1 = InitObject(new WallFullMock(nullptr));
	MakeSolid(wall1);

	// Стена изначально расположена параллельно оси y
	auto wall2 = InitObject(new WallFullMock(nullptr));
	wall2->GetTransform()->GetPosition()->z(FoundationSquare::m_ModelSize);
	MakeSolid(wall2);

	auto wall1Links = ConnectionManager::Instance().GetAdditionals(wall1);
	auto wall2Links = ConnectionManager::Instance().GetAdditionals(wall2);

	BOOST_CHECK_EQUAL(wall1Links.size(), 0);
	BOOST_CHECK_EQUAL(wall2Links.size(), 0);

	delete wall1;
	delete wall2;

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_SUITE_END()