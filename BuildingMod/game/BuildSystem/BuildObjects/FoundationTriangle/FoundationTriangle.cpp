#include "FoundationTriangle.h"

#include "TriangleCollider.h"

#include <game/BuildSystem/BuildObjects/Components/OwnerComponent.h>
#include <game/BuildSystem/BuildObjects/Components/RendererComponent.h>
#include <game/BuildSystem/BuildObjects/Components/IColliderComponent.h>

#include <game/Utility/Utility.h>
#include <game/Server/PrecacheManager.h>

FoundationTriangle::FoundationTriangle(edict_t *owner) : Foundation(owner)
{
}

void FoundationTriangle::Start()
{
	GameObject::Start();

	auto renderer = new RendererComponent;
	renderer->SetModel(PrecacheManager::Instance().GetFoundationTriangleModel());

	AddComponent(renderer);

	auto collider = new TriangleCollider;
	collider->AddEdict(UTIL_CreateEdict("info_target"), true);
	collider->AddEdict(UTIL_CreateEdict("info_target"), false);
	collider->AddEdict(UTIL_CreateEdict("info_target"), false);

	AddComponent(collider);

	for (auto pEntity : collider->GetEdicts(true))
	{
		auto model = (char *)STRING(UTIL_AllocString(renderer->GetModel()));
		SET_MODEL(pEntity, model);
	}

	for (auto pEntity : collider->GetEdicts(false))
	{
		auto model = (char *)STRING(UTIL_AllocString(renderer->GetModel()));
		SET_MODEL(pEntity, model);
	}
}

void FoundationTriangle::Update()
{
	GameObject::Update();

	if (m_State != BuildState::STATE_SOLID)
	{
		AimPointHandler();
	}
}

void FoundationTriangle::AimPointHandler()
{
	auto owner = GetComponent<OwnerComponent>()->GetOwner();

	auto viewPoint = UTIL_GetEndPoint(ENTINDEX(owner), 300.0f);
	viewPoint.z += m_MinHeight;

	bool isTestPassed = TraceGroundTest(viewPoint, owner->v.v_angle);

	TrySetState(isTestPassed ? BuildState::STATE_CAN_BUILD : BuildState::STATE_CANNOT_BUILD);

	GetTransform()->GetPosition()->setVector(viewPoint.x, viewPoint.y, viewPoint.z);
	GetTransform()->GetRotation()->y(owner->v.v_angle.y + 180);
}

bool FoundationTriangle::TraceGroundTest(Vector viewPoint, Vector viewAngle)
{
	TraceResult tr;

	int numHits = 0;
	vector<Vector> startPoints{
		viewPoint,
		viewPoint + UTIL_Rotate(Vector(60, 0, 0), viewAngle.y + 90),
		viewPoint + UTIL_Rotate(Vector(60, 0, 0), viewAngle.y + 210),
		viewPoint + UTIL_Rotate(Vector(60, 0, 0), viewAngle.y - 30),
	};

	float maxHeight = 0;

	for (Vector &startPoint : startPoints)
	{
		UTIL_TraceLine(startPoint, startPoint - Vector(0, 0, 1000),
					   IGNORE_MONSTERS::dont_ignore_monsters,
					   nullptr, &tr);

		auto vDest = tr.vecEndPos - startPoint;

		if (vDest.Length() > m_MaxHeight)
		{
			if (maxHeight < vDest.Length())
				maxHeight = vDest.Length();

			continue;
		}

		if (tr.pHit)
			numHits++;
	}

	if (numHits >= 3)
		return true;

	if (maxHeight <= 140)
	{
		viewPoint.z = viewPoint.z - maxHeight + m_MaxHeight;

		return TraceGroundTest(viewPoint, viewAngle);
	}

	return false;
}
