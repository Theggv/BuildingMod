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

	auto renderer = new RendererComponent;
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

// NOTE - idk is it works
AimTestResult WallFull::AimTest(ray ray)
{
	auto objects = ObjectManager::Instance().GetObjectsInArea(ray.GetOrigin());
	auto it = objects.begin();

	while (it != objects.end())
	{
		if (it->empty() || it->expired())
		{
			it->reset();
			it = objects.erase(it);
			continue;
		}

		if (dynamic_cast<FoundationBase *>(*it->lock()) == nullptr &&
			dynamic_cast<WallBase *>(*it->lock()) == nullptr)
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
		vec3 posA = *(*a_ptr.lock())->GetTransform()->GetPosition();
		vec3 posB = *(*b_ptr.lock())->GetTransform()->GetPosition();

		auto distVec1 = posA - ray.GetOrigin();
		auto distVec2 = posB - ray.GetOrigin();

		return distVec1.LengthSquared() < distVec2.LengthSquared();
	});

	for (auto &object_p : objects)
	{
		auto object = *object_p.lock();

		auto stability = object->GetComponent<IStabilityComponent>();
		auto result = stability->TryConnect(ray, this);

		if (result.m_IsPassed)
			return result;
	}

	return AimTestResult(false, ray.GetDest(), ray.GetVectorAngle());
}

Shape WallFull::GetShape(AimTestResult res)
{
	auto half = m_ModelSize / 2 - 1;
	auto full = m_ModelSize - 1;

	std::vector<vec3> points = {
		vec3(-half, 0, 0),
		vec3(half, 0, 0),
		vec3(half, 0, full),
		vec3(-half, 0, full),
	};

	mat4 mat = mat4::RotationMatrix(90 - res.m_Angle) *
			   mat4::TranslateMatrix(res.m_Origin);

	for (size_t i = 0; i < points.size(); i++)
	{
		points[i] = points[i].Transform(mat);
	}

	return Shape(points);
}