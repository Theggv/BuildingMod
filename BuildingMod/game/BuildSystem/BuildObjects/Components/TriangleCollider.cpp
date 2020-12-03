#include "TriangleCollider.h"

void TriangleCollider::AddEdict(edict_t* edict, bool isVisible)
{
	if (isVisible)
		m_VisibleEdicts.insert(edict);
	else
	{
		m_InvisibleEdicts.insert(edict);

		edict->v.rendermode = kRenderTransAlpha;
		edict->v.renderamt = 0.0f;
	}
}

set<edict_t*> TriangleCollider::GetEdicts(bool isVisible)
{
	return isVisible ? m_VisibleEdicts : m_InvisibleEdicts;
}

void TriangleCollider::UpdateTransform()
{
	for (auto pEntity : m_VisibleEdicts)
	{
		SET_ORIGIN(pEntity, GetParent()->GetTransform()->GetPosition()->ToRound());
		pEntity->v.angles = *GetParent()->GetTransform()->GetRotation();
	}

	int i = 1;
	for (auto pEntity : m_InvisibleEdicts)
	{
		SET_ORIGIN(pEntity, GetParent()->GetTransform()->GetPosition()->ToRound());
		pEntity->v.angles = *GetParent()->GetTransform()->GetRotation();

		// set y
		pEntity->v.angles.y = GetParent()->GetTransform()->GetRotation()->y() + (120 * i++);
	}
}