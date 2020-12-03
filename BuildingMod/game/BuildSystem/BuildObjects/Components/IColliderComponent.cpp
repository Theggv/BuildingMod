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
		SET_ORIGIN(pEntity, GetParent()->GetTransform()->GetPosition()->ToRound());
		pEntity->v.angles = *GetParent()->GetTransform()->GetRotation();
	}

	for (auto pEntity : m_InvisibleEdicts)
	{
		SET_ORIGIN(pEntity, GetParent()->GetTransform()->GetPosition()->ToRound());
		pEntity->v.angles = *GetParent()->GetTransform()->GetRotation();
	}
}

void IColliderComponent::StateUpdated()
{
	auto state = m_parent->GetState();

	switch (state)
	{
	case BuildState::STATE_SOLID:
		for (auto pEntity : m_VisibleEdicts)
		{
			pEntity->v.solid = SOLID_BBOX;
			SET_SIZE(pEntity, Vector(-64, -64, 0), Vector(64, 64, 128));

			pEntity->v.rendermode = kRenderNormal;
			pEntity->v.renderfx = kRenderFxNone;
		}

		for (auto pEntity : m_InvisibleEdicts)
		{
			pEntity->v.solid = SOLID_BBOX;
			SET_SIZE(pEntity, Vector(-64, -64, 0), Vector(64, 64, 128));
		}

		break;
	case BuildState::STATE_CANNOT_BUILD:
		for (auto pEntity : m_VisibleEdicts)
		{
			pEntity->v.solid = SOLID_NOT;

			pEntity->v.rendermode = kRenderTransAlpha;
			pEntity->v.renderamt = 150.0f;
			pEntity->v.rendercolor = Vector(255, 0, 0);
			pEntity->v.renderfx = kRenderFxGlowShell;
		}

		for (auto pEntity : m_InvisibleEdicts)
			pEntity->v.solid = SOLID_NOT;

		break;
	case BuildState::STATE_CAN_BUILD:
		for (auto pEntity : m_VisibleEdicts)
		{
			pEntity->v.solid = SOLID_NOT;

			pEntity->v.rendermode = kRenderTransAlpha;
			pEntity->v.renderamt = 150.0f;
			pEntity->v.rendercolor = Vector(50, 50, 255);
			pEntity->v.renderfx = kRenderFxGlowShell;
		}

		for (auto pEntity : m_InvisibleEdicts)
			pEntity->v.solid = SOLID_NOT;

		break;
	}
}
