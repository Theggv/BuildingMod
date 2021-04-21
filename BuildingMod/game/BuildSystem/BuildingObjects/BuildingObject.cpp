#include "BuildingObject.h"
#include <game/BuildSystem/Components/IStabilityComponent.h>

BuildingObject::BuildingObject(edict_t *owner)
{
	AddComponent(new OwnerComponent(owner));
}

Shape BuildingObject::GetShape()
{
	return GetShape(AimTestResult(
		true,
		*GetTransform()->GetPosition(),
		GetTransform()->GetRotation()->y()));
}