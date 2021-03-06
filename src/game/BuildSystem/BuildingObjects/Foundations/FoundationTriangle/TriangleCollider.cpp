#include "TriangleCollider.h"
#include <Utility/EdictFlags.h>
#include <game/BuildSystem/Components/RendererComponent.h>

TriangleCollider::TriangleCollider()
{
	auto width = 120.0;
	auto height = width * sin(60 * M_PI / 180);

	auto minH = (height / 3) - (height / 2);
	auto maxH = height + minH;

	m_Shape = new Shape({
		vec2(-width / 2, minH),
		vec2(0, maxH),
		vec2(width / 2, minH),
	});
}

void TriangleCollider::AddEdict(edict_t *edict, bool isVisible)
{
	if (isVisible)
		m_VisibleEdicts.insert(edict);
	else
	{
		m_InvisibleEdicts.insert(edict);

		edict->v.rendermode = kRenderTransAlpha;
		edict->v.renderamt = 0.0f;
	}

	EdictFlags::SetFlags(edict, m_Parent->Id);
}

set<edict_t *> TriangleCollider::GetEdicts(bool isVisible)
{
	return isVisible ? m_VisibleEdicts : m_InvisibleEdicts;
}

void TriangleCollider::OnTransformUpdate()
{
	auto renderer = m_Parent->GetComponent<RendererComponent>();
	double fixAngle = renderer != nullptr ? renderer->GetFixAngle() : 0;

	for (auto pEntity : m_VisibleEdicts)
	{
		SET_ORIGIN(pEntity, GetParent()->GetTransform()->GetPosition()->ToRound());
		pEntity->v.angles = *GetParent()->GetTransform()->GetRotation();
		pEntity->v.angles.y = pEntity->v.angles.y + fixAngle;
	}

	int i = 1;

	for (auto pEntity : m_InvisibleEdicts)
	{
		SET_ORIGIN(pEntity, GetParent()->GetTransform()->GetPosition()->ToRound());
		pEntity->v.angles = *GetParent()->GetTransform()->GetRotation();

		// set y
		auto y = GetParent()->GetTransform()->GetRotation()->y() + (120 * i++);

		while (y > 180)
			y -= 360;

		pEntity->v.angles.y = y + fixAngle;
	}
}