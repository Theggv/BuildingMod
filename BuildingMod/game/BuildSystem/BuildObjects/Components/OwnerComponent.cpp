#include "OwnerComponent.h"

#include <game/Utility/Utility.h>

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

	// SEM_PRINT("[Building Mod] [%.1f %.1f %.1f] %.1f",
	// 		  m_Owner->v.origin.x,
	// 		  m_Owner->v.origin.y,
	// 		  m_Owner->v.origin.z,
	// 		  m_Owner->v.v_angle.y);
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
