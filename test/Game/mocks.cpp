#include "mocks.h"

WallFullMock::WallFullMock(edict_t *owner) : WallFull(owner)
{
}

void WallFullMock::OnStart()
{
	WallBase::OnStart();

	auto stability = new WallFullResolvers::StabilityComponent;
	AddComponent(stability);
}

FoundationSquareMock::FoundationSquareMock(edict_t *owner) : FoundationSquare(owner)
{
}

void FoundationSquareMock::OnStart()
{
	FoundationBase::OnStart();

	auto stability = new FoundationSquareResolvers::StabilityComponent;
	AddComponent(stability);
}

GameObject *InitObject(GameObject *object)
{
	ObjectManager::Instance().Add(object);
	return object;
}

void MakeSolid(GameObject *object)
{
	object->TrySetState(BuildState::STATE_CAN_BUILD);
	object->TrySetState(BuildState::STATE_SOLID);
}