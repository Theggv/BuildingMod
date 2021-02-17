#include "OwnerComponent.h"

#include <game/Utility/Utility.h>
#include <game/Utility/EdictFlags.h>

OwnerComponent::OwnerComponent(edict_t *owner)
{
	m_Owner = owner;
}

OwnerComponent::~OwnerComponent()
{
}

void OwnerComponent::Update()
{
	IComponent::Update();
}

void OwnerComponent::StateUpdated()
{
	if (m_Parent->GetState() == BuildState::STATE_SOLID)
	{
		EdictFlags::SetPlayerSelectedObject(m_Owner, 0);
	}
}

edict_t *OwnerComponent::GetOwner()
{
	return m_Owner;
}

void OwnerComponent::SetOwner(edict_t *owner)
{
	m_Owner = owner;
}

vec3 OwnerComponent::GetViewAngles()
{
	return vec3(m_Owner->v.v_angle);
}

vec3 OwnerComponent::GetAimDest(double maxTriggerDistance)
{
	auto viewPoint = UTIL_GetEndPoint(ENTINDEX(m_Owner), maxTriggerDistance);

	return vec3(viewPoint);
}

ray OwnerComponent::GetAimRay(vec3 destination, double maxRayLength)
{
	auto origin = m_Owner->v.origin;

	return ray(
		vec3(origin),
		vec3(destination) - vec3(origin),
		maxRayLength);
}
