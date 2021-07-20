#include <pch.h>

#include <game/BuildSystem/BuildingObjects/Objects.h>
#include <game/BuildSystem/BuildingObjects/Foundations/FoundationSquare/StabilityComponent.h>
#include <game/BuildSystem/BuildingObjects/Walls/WallFull/StabilityComponent.h>
#include <game/BuildSystem/ConnectionManager.h>

class FoundationSquareMock : public FoundationSquare
{
public:
	FoundationSquareMock(edict_t *owner);

	virtual void OnStart() override;
};

class WallFullMock : public WallFull
{
public:
	WallFullMock(edict_t *owner);

	virtual void OnStart() override;
};

p_GameObject_t InitObject(GameObject* object);

void MakeSolid(p_GameObject_t object);