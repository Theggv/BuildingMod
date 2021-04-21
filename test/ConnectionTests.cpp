#define BOOST_TEST_MODULE ConnectionTests

#include <pch.h>
#include <boost/test/included/unit_test.hpp>

#include <game/BuildSystem/BuildingObjects/Objects.h>
#include <game/BuildSystem/BuildingObjects/Foundations/FoundationSquare/StabilityComponent.h>
#include <game/BuildSystem/BuildingObjects/Walls/WallFull/StabilityComponent.h>
#include <game/BuildSystem/ConnectionManager.h>

class FoundationSquareMock : public FoundationSquare
{
public:
	FoundationSquareMock(edict_t *owner) : FoundationSquare(owner) {}

	virtual void OnStart() override
	{
		FoundationBase::OnStart();

		auto stability = new FoundationSquareResolvers::StabilityComponent;
		AddComponent(stability);
	}
};

class WallFullMock : public WallFull
{
public:
	WallFullMock(edict_t *owner) : WallFull(owner) {}

	virtual void OnStart() override
	{
		WallBase::OnStart();

		auto stability = new WallFullResolvers::StabilityComponent;
		AddComponent(stability);
	}
};

template <class T = GameObject>
T *InitObject(T *object)
{
	ObjectManager::Instance().Add(object);
	return object;
}

void MakeSolid(GameObject *object)
{
	object->TrySetState(BuildState::STATE_CAN_BUILD);
	object->TrySetState(BuildState::STATE_SOLID);
}

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

	// TODO not implemented yet
	// BOOST_CHECK_EQUAL(links3.size(), 1); 
	BOOST_CHECK_EQUAL(links4.size(), 2);

	delete foundation1;
	delete foundation2;

	delete wall1;
	delete wall2;

	ObjectManager::Instance().Clear();
}