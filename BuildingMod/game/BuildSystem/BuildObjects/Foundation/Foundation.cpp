#include "Foundation.h"

#include <game/BuildSystem/BuildObjects/Components/OwnerComponent.h>
#include <game/BuildSystem/BuildObjects/Components/RendererComponent.h>
#include <game/BuildSystem/BuildObjects/Components/IColliderComponent.h>

#include <game/Utility/Utility.h>
#include <game/Server/PrecacheManager.h>

Foundation::Foundation(edict_t* owner)
{
	AddComponent(new OwnerComponent(owner));

	// m_Shape = new CPolygon({
	// 	Point(-64,-64),
	// 	Point(-64, 64),
	// 	Point(64, 64),
	// 	Point(64, -64)
	// 	});
}

void Foundation::Start()
{
	auto renderer = new RendererComponent;
	renderer->SetModel(PrecacheManager::Instance().GetFoundationModel());

	AddComponent(renderer);

	auto collider = new IColliderComponent;
	collider->AddEdict(UTIL_CreateEdict("info_target"), true);

	AddComponent(collider);

	for (auto pEntity : collider->GetEdicts(true))
	{
		auto model = (char*)STRING(UTIL_AllocString(renderer->GetModel()));
		SET_MODEL(pEntity, model);
	}
}

void Foundation::Update()
{
	if (m_State != BuildState::STATE_SOLID)
	{
		AimPointHandler();
	}
}

void Foundation::AimPointHandler()
{
	auto owner = GetComponent<OwnerComponent>()->GetOwner();

	auto viewPoint = UTIL_GetEndPoint(ENTINDEX(owner), 300.0f);
	viewPoint.z += m_MinHeight;

	bool isTestPassed = TraceGroundTest(viewPoint, owner->v.v_angle);

	TrySetState(isTestPassed ? BuildState::STATE_CAN_BUILD : BuildState::STATE_CANNOT_BUILD);

	GetTransform()->GetPosition()->setVector(viewPoint.x, viewPoint.y, viewPoint.z);
	GetTransform()->GetRotation()->y(owner->v.v_angle.y);
}

bool Foundation::TraceGroundTest(Vector& viewPoint, Vector& viewAngle)
{
	TraceResult tr;

	int numHits = 0;
	vector<Vector> startPoints
	{
		viewPoint,
		viewPoint + UTIL_Rotate(Vector(-56, -56, 0), viewAngle.y),
		viewPoint + UTIL_Rotate(Vector(-56, 56, 0), viewAngle.y),
		viewPoint + UTIL_Rotate(Vector(56, -56, 0), viewAngle.y),
		viewPoint + UTIL_Rotate(Vector(56, 56, 0), viewAngle.y),
	};

	float maxHeight = 0;

	for (Vector& startPoint : startPoints)
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

	if (numHits >= 4)
		return true;

	if (maxHeight <= 140)
	{
		viewPoint.z = viewPoint.z - maxHeight + m_MaxHeight;

		return TraceGroundTest(viewPoint, viewAngle);
	}

	return false;
}
