#include "BuildingObject.h"
#include <game/BuildSystem/Components/IStabilityComponent.h>

BuildingObject::BuildingObject(edict_t *owner)
{
	AddComponent(new OwnerComponent(owner));
}

void BuildingObject::Connect(GameObject *other)
{
	if (this->GetComponent<IStabilityComponent>())
		this->GetComponent<IStabilityComponent>()->AddConnection(other);

	if (other->GetComponent<IStabilityComponent>())
		other->GetComponent<IStabilityComponent>()->AddConnection(this);
}

Shape BuildingObject::GetShape()
{
	return GetShape(AimTestResult(
		true,
		*GetTransform()->GetPosition(),
		GetTransform()->GetRotation()->y()));
}