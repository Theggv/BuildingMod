#include <pch.h>
#include <boost/test/unit_test.hpp>
#include "mocks.h"

BOOST_AUTO_TEST_SUITE(StabilitySuite)

BOOST_AUTO_TEST_CASE(WallStabilityTest1)
{
	auto foundation1 = InitObject(new FoundationSquareMock(nullptr));
	MakeSolid(foundation1);

	auto wall1 = InitObject(new WallFullMock(nullptr));
	wall1->GetTransform()->GetPosition()->y(WallBase::m_ModelSize / 2);
	MakeSolid(wall1);

	BOOST_TEST(foundation1->GetComponent<IStabilityComponent>()->GetStability() == 1.0,
			   boost::test_tools::tolerance(0.001));

	BOOST_TEST(wall1->GetComponent<IStabilityComponent>()->GetStability() == 0.7,
			   boost::test_tools::tolerance(0.001));

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_CASE(WallStabilityTest2)
{
	auto foundation1 = InitObject(new FoundationSquareMock(nullptr));
	auto wall1 = InitObject(new WallFullMock(nullptr));
	auto wall2 = InitObject(new WallFullMock(nullptr));

	MakeSolid(foundation1);
	MakeSolid(wall1);
	MakeSolid(wall2);

	ConnectionManager::Instance().AddLinkParentChild(foundation1, wall1);
	ConnectionManager::Instance().AddLinkParentChild(foundation1, wall2);
	ConnectionManager::Instance().AddLinkAdditional(wall1, wall2);

	BOOST_TEST(wall1->GetComponent<IStabilityComponent>()->GetStability() == 0.7777,
			   boost::test_tools::tolerance(0.001));

	BOOST_TEST(wall2->GetComponent<IStabilityComponent>()->GetStability() == 0.7777,
			   boost::test_tools::tolerance(0.001));

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_CASE(WallStabilityTest3)
{
	auto foundation1 = InitObject(new FoundationSquareMock(nullptr));
	auto wall1 = InitObject(new WallFullMock(nullptr));
	auto wall2 = InitObject(new WallFullMock(nullptr));

	MakeSolid(foundation1);
	MakeSolid(wall1);
	MakeSolid(wall2);

	ConnectionManager::Instance().AddLinkParentChild(foundation1, wall1);
	ConnectionManager::Instance().AddLinkAdditional(wall1, wall2);

	BOOST_TEST(wall1->GetComponent<IStabilityComponent>()->GetStability() == 0.7070,
			   boost::test_tools::tolerance(0.001));

	BOOST_TEST(wall2->GetComponent<IStabilityComponent>()->GetStability() == 0.0707,
			   boost::test_tools::tolerance(0.001));

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_SUITE_END()