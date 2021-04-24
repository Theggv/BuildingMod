#include "WallFull.h"
#include "StabilityComponent.h"

#include <game/BuildSystem/Components/OwnerComponent.h>
#include <game/BuildSystem/Components/RendererComponent.h>
#include <game/BuildSystem/Components/IColliderComponent.h>
#include <game/BuildSystem/Components/VisualizerComponent.h>
#include <game/BuildSystem/Components/IStabilityComponent.h>

#include <game/Utility/Utility.h>
#include <game/Server/PrecacheManager.h>

// objects
#include <game/BuildSystem/BuildingObjects/Foundations/Foundations.h>

using namespace WallFullResolvers;

const double WallFull::m_Height = m_ModelSize;

WallFull::WallFull(edict_t *owner) : WallBase(owner)
{
}

void WallFull::OnStart()
{
	WallBase::OnStart();

	auto renderer = new RendererComponent(-90);
	renderer->SetModel(PrecacheManager::Instance().GetWallModel());

	AddComponent(renderer);

	auto collider = new IColliderComponent;
	AddComponent(collider);

	collider->AddEdict(UTIL_CreateEdict("info_target"), true);

	for (auto pEntity : collider->GetEdicts(true))
	{
		auto model = (char *)STRING(UTIL_AllocString(renderer->GetModel()));
		SET_MODEL(pEntity, model);
	}

	auto triggerZone = new StabilityComponent;
	AddComponent(triggerZone);
}

// NOTE - idk does it work
AimTestResult WallFull::AimTest(ray ray)
{
	auto objects = ObjectManager::Instance().GetObjectsInArea(ray.GetOrigin());
	auto it = objects.begin();

	while (it != objects.end())
	{
		if (it->expired())
		{
			it = objects.erase(it);
			continue;
		}

		auto object = it->lock();

		if (dynamic_pointer_cast<FoundationBase>(object) == nullptr &&
			dynamic_pointer_cast<WallBase>(object) == nullptr)
		{
			it->reset();
			it = objects.erase(it);
			continue;
		}

		++it;
	}

	if (!objects.size())
		return AimTestResult(false, ray.GetDest(), ray.GetVectorAngle());

	sort(objects.begin(), objects.end(), [&ray](const p_GameObjectWeak_t a_ptr, const p_GameObjectWeak_t b_ptr) {
		vec3 posA = *(a_ptr.lock())->GetTransform()->GetPosition();
		vec3 posB = *(b_ptr.lock())->GetTransform()->GetPosition();

		auto distVec1 = posA - ray.GetOrigin();
		auto distVec2 = posB - ray.GetOrigin();

		return distVec1.LengthSquared() < distVec2.LengthSquared();
	});

	for (auto &object_p : objects)
	{
		auto object = object_p.lock();

		auto stability = object->GetComponent<IStabilityComponent>();
		auto result = stability->TryConnect(ray, this->GetSharedPtr());

		if (result.m_IsPassed)
			return result;
	}

	return AimTestResult(false, ray.GetDest(), ray.GetVectorAngle());
}

Shape WallFull::GetShape(AimTestResult res)
{
	auto half = m_ModelSize / 2;
	auto full = m_ModelSize;

	std::vector<vec3> points = {
		vec3(0, -half, 0),
		vec3(0, half, 0),
		vec3(0, half, full),
		vec3(0, -half, full),
	};

	Shape shape(points);
	shape.SetAngle(res.m_Angle);
	shape.SetPosition(res.m_Origin);

	return shape;
}