#include "BuildingObject.h"

BuildingObject::BuildingObject(edict_t *owner)
{
}

Shape BuildingObject::GetShape()
{
	return GetShape(AimTestResult(
		true,
		*GetTransform()->GetPosition(),
		GetTransform()->GetRotation()->y()));
}