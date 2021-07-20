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

p_GameObject_t InitObject(GameObject *object)
{
	auto ptr = ObjectManager::Instance().Get(object->Id);
	ptr->OnStart();
	return ptr;
}

void MakeSolid(p_GameObject_t object)
{
	object->TrySetState(BuildState::STATE_CAN_BUILD);
	object->TrySetState(BuildState::STATE_SOLID);
}