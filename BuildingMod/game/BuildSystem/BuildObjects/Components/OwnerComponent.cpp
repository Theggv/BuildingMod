#include "OwnerComponent.h"

OwnerComponent::OwnerComponent(edict_t* owner)
{
	m_Owner = owner;
}

OwnerComponent::~OwnerComponent()
{
}

edict_t* OwnerComponent::GetOwner()
{
	return m_Owner;
}

void OwnerComponent::SetOwner(edict_t* owner)
{
	m_Owner = owner;
}
