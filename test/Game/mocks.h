#include <pch.h>

#include <game/BuildSystem/BuildingObjects/Objects.h>
#include <game/BuildSystem/BuildingObjects/Foundations/FoundationSquare/StabilityComponent.h>
#include <game/BuildSystem/BuildingObjects/Walls/WallFull/StabilityComponent.h>
#include <game/BuildSystem/ConnectionManager.h>

class FoundationSquareMock : public FoundationSquare
{
public:
	FoundationSquareMock(edict_t *owner) : FoundationSquare(owner) {}

	inline virtual void OnStart() override
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

	inline virtual void OnStart() override
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

inline void MakeSolid(GameObject *object)
{
	object->TrySetState(BuildState::STATE_CAN_BUILD);
	object->TrySetState(BuildState::STATE_SOLID);
}