#include "Foundation.h"

#include <game/BuildSystem/BuildObjects/Components/OwnerComponent.h>
#include <game/BuildSystem/BuildObjects/Components/RendererComponent.h>
#include <game/BuildSystem/BuildObjects/Components/IColliderComponent.h>

#include <game/Utility/Utility.h>
#include <game/Server/PrecacheManager.h>

Foundation::Foundation(edict_t* owner)
{
	AddComponent(new OwnerComponent(owner));

	auto renderer = new RendererComponent;
	renderer->SetModel(PrecacheManager::Instance().GetFoundationModel());

	AddComponent(renderer);

	auto collider = new IColliderComponent;
	collider->AddEdict(UTIL_CreateEdict("info_target"), true);

	AddComponent(collider);
}

void Foundation::Start()
{
	auto renderer = GetComponent<RendererComponent>();
	auto collider = GetComponent<IColliderComponent>();

	for (auto pEntity : collider->GetEdicts(true))
	{
		auto model = STRING(UTIL_AllocString(renderer->GetModel()));
		SET_MODEL(pEntity, model);
	}
}

void Foundation::Update()
{
	if (m_State != BuildState::STATE_SOLID)
	{
		auto owner = GetComponent<OwnerComponent>()->GetOwner();
	
		auto viewPoint = UTIL_GetEndPoint(ENTINDEX(owner), 300.0f);

		GetTransform()->GetPosition()->setVector(viewPoint.x, viewPoint.y, viewPoint.z);
		GetTransform()->GetRotation()->y(owner->v.v_angle.y);
	}
}
