#include "IColliderComponent.h"
#include <Utility/EdictFlags.h>
#include "RendererComponent.h"

IColliderComponent::IColliderComponent()
{
	m_VisibleEdicts = set<edict_t *>();
	m_InvisibleEdicts = set<edict_t *>();
}

IColliderComponent::~IColliderComponent()
{
	for (auto edict : m_VisibleEdicts)
		REMOVE_ENTITY(edict);

	for (auto edict : m_InvisibleEdicts)
		REMOVE_ENTITY(edict);

	set<edict_t *>().swap(m_VisibleEdicts);
	set<edict_t *>().swap(m_InvisibleEdicts);

	delete m_Shape;
}

void IColliderComponent::AddEdict(edict_t *edict, bool isVisible)
{
	if (isVisible)
		m_VisibleEdicts.insert(edict);
	else
		m_InvisibleEdicts.insert(edict);

	EdictFlags::SetFlags(edict, GetParent()->Id);
}

set<edict_t *> IColliderComponent::GetEdicts(bool isVisible)
{
	return isVisible ? m_VisibleEdicts : m_InvisibleEdicts;
}

void IColliderComponent::OnTransformUpdate()
{
	auto renderer = GetParent()->GetComponent<RendererComponent>();
	double fixAngle = renderer != nullptr ? renderer->GetFixAngle() : 0;

	for (auto pEntity : m_VisibleEdicts)
	{
		SET_ORIGIN(pEntity, GetParent()->GetTransform()->GetPosition()->ToRound());
		pEntity->v.angles = *GetParent()->GetTransform()->GetRotation();
		pEntity->v.angles.y = pEntity->v.angles.y + fixAngle;
	}

	for (auto pEntity : m_InvisibleEdicts)
	{
		SET_ORIGIN(pEntity, GetParent()->GetTransform()->GetPosition()->ToRound());
		pEntity->v.angles = *GetParent()->GetTransform()->GetRotation();
		pEntity->v.angles.y = pEntity->v.angles.y + fixAngle;
	}
}

void IColliderComponent::OnStateUpdated()
{
	auto state = GetParent()->GetState();

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
			pEntity->v.rendercolor = Vector(0, 0, 255);
			pEntity->v.renderfx = kRenderFxGlowShell;
		}

		for (auto pEntity : m_InvisibleEdicts)
			pEntity->v.solid = SOLID_NOT;

		break;
	}
}
