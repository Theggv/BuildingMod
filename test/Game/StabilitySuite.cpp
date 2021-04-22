#include <pch.h>
#include <boost/test/unit_test.hpp>
#include "mocks.h"

#include <game/BuildSystem/BuildingObjects/Objects.h>
#include <game/BuildSystem/BuildingObjects/Foundations/FoundationSquare/StabilityComponent.h>
#include <game/BuildSystem/BuildingObjects/Walls/WallFull/StabilityComponent.h>
#include <game/BuildSystem/ConnectionManager.h>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(StabilitySuite)

BOOST_AUTO_TEST_CASE(WallStabilityTest1)
{
	auto foundation1 = InitObject(new FoundationSquareMock(nullptr));
	auto wall1 = InitObject(new WallFullMock(nullptr));

	ConnectionManager::Instance().AddLinkParentChild(foundation1, wall1);

	BOOST_TEST(foundation1->GetComponent<IStabilityComponent>()->GetStability() == 1.0,
			   tt::tolerance(0.001));

	BOOST_TEST(wall1->GetComponent<IStabilityComponent>()->GetStability() == 0.7,
			   tt::tolerance(0.001));

	delete foundation1;
	delete wall1;

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_CASE(WallStabilityTest2)
{
	auto foundation1 = InitObject(new FoundationSquareMock(nullptr));
	auto wall1 = InitObject(new WallFullMock(nullptr));
	auto wall2 = InitObject(new WallFullMock(nullptr));

	ConnectionManager::Instance().AddLinkParentChild(foundation1, wall1);
	ConnectionManager::Instance().AddLinkParentChild(foundation1, wall2);
	ConnectionManager::Instance().AddLinkAdditional(wall1, wall2);

	BOOST_TEST(wall1->GetComponent<IStabilityComponent>()->GetStability() == 0.7777,
			   tt::tolerance(0.001));

	BOOST_TEST(wall2->GetComponent<IStabilityComponent>()->GetStability() == 0.7777,
			   tt::tolerance(0.001));

	delete foundation1;
	delete wall1;
	delete wall2;

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_CASE(WallStabilityTest3)
{
	auto foundation1 = InitObject(new FoundationSquareMock(nullptr));
	auto wall1 = InitObject(new WallFullMock(nullptr));
	auto wall2 = InitObject(new WallFullMock(nullptr));

	ConnectionManager::Instance().AddLinkParentChild(foundation1, wall1);
	ConnectionManager::Instance().AddLinkAdditional(wall1, wall2);

	BOOST_TEST(wall1->GetComponent<IStabilityComponent>()->GetStability() == 0.7070,
			   tt::tolerance(0.001));

	BOOST_TEST(wall2->GetComponent<IStabilityComponent>()->GetStability() == 0.0707,
			   tt::tolerance(0.001));

	delete foundation1;
	delete wall1;
	delete wall2;

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_SUITE_END()