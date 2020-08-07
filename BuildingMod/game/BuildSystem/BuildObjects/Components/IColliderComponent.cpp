#include "IColliderComponent.h"

IColliderComponent::IColliderComponent()
{
	m_VisibleEdicts = set<edict_t*>();
	m_InvisibleEdicts = set<edict_t*>();
}

IColliderComponent::~IColliderComponent()
{
	for (auto edict : m_VisibleEdicts)
		REMOVE_ENTITY(edict);

	for (auto edict : m_InvisibleEdicts)
		REMOVE_ENTITY(edict);

	m_VisibleEdicts.clear();
	m_InvisibleEdicts.clear();
}

void IColliderComponent::AddEdict(edict_t* edict, bool isVisible)
{
	if (isVisible)
		m_VisibleEdicts.insert(edict);
	else
		m_InvisibleEdicts.insert(edict);
}

set<edict_t*> IColliderComponent::GetEdicts(bool isVisible)
{
	return isVisible ? m_VisibleEdicts : m_InvisibleEdicts;
}

void IColliderComponent::UpdateTransform()
{
	for (auto pEntity : m_VisibleEdicts)
	{
		pEntity->v.origin = *GetParent()->GetTransform()->GetPosition();
		pEntity->v.angles = *GetParent()->GetTransform()->GetRotation();
	}

	for (auto pEntity : m_InvisibleEdicts)
	{
		pEntity->v.origin = *GetParent()->GetTransform()->GetPosition();
		pEntity->v.angles = *GetParent()->GetTransform()->GetRotation();
	}
}
