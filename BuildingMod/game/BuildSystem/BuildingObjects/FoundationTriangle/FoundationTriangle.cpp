#include "FoundationTriangle.h"
#include "StabilityComponent.h"

#include "TriangleCollider.h"

#include <game/BuildSystem/Components/OwnerComponent.h>
#include <game/BuildSystem/Components/RendererComponent.h>
#include <game/BuildSystem/Components/IColliderComponent.h>
#include <game/BuildSystem/Components/VisualizerComponent.h>

#include <game/Utility/Utility.h>
#include <game/Server/PrecacheManager.h>
#include <game/Server/FrameState.h>

using namespace FoundationTriangleResolvers;

const double FoundationTriangle::m_Height = m_ModelSize * sin(60 * M_PI / 180);

FoundationTriangle::FoundationTriangle(edict_t *owner) : FoundationBase(owner)
{
}

void FoundationTriangle::OnStart()
{
	GameObject::OnStart();

	auto renderer = new RendererComponent;
	renderer->SetModel(PrecacheManager::Instance().GetFoundationTriangleModel());

	AddComponent(renderer);

	auto collider = new TriangleCollider;
	AddComponent(collider);

	collider->AddEdict(UTIL_CreateEdict("info_target"), true);
	collider->AddEdict(UTIL_CreateEdict("info_target"), false);
	collider->AddEdict(UTIL_CreateEdict("info_target"), false);

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

	auto triggerZone = new StabilityComponent;
	AddComponent(triggerZone);
}

void FoundationTriangle::OnUpdate()
{
	GameObject::OnUpdate();

	if (m_State != BuildState::STATE_SOLID)
	{
		AimPointHandler();
	}
}

AimTestResult FoundationTriangle::TraceGroundTest(AimTestResult &result)
{
	TraceResult tr;

	int numHits = 0;
	vector<vec3> points{
		vec3::Zero(),
		vec3(0, 40).Transform(mat4::RotationMatrix(0)),
		vec3(0, 40).Transform(mat4::RotationMatrix(-120)),
		vec3(0, 40).Transform(mat4::RotationMatrix(120)),
	};

	auto mat = mat4::RotationMatrix(result.m_Angle) *
			   mat4::TranslateMatrix(result.m_Origin);

	for (size_t i = 0; i < points.size(); i++)
	{
		points[i] = points[i].Transform(mat);
	}

	float maxHeight = 0;

	for (auto &point : points)
	{
		auto converted = Vector(point.x, point.y, point.z);

		UTIL_TraceLine(converted, converted - Vector(0, 0, 1000),
					   IGNORE_MONSTERS::dont_ignore_monsters,
					   nullptr, &tr);

		auto vDest = tr.vecEndPos - converted;

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
		return AimTestResult(true, result.m_Origin, result.m_Angle);

	if (maxHeight <= 150)
	{
		result.m_Origin.z = result.m_Origin.z - 1;

		return TraceGroundTest(result);
	}

	return AimTestResult(false, result.m_Origin, result.m_Angle);
}

AimTestResult FoundationTriangle::FoundationAimTest(ray ray)
{
	auto objects = ObjectManager::Instance().GetObjectsInArea(ray.GetOrigin());
	auto it = objects.begin();

	while (it != objects.end())
	{
		// remove empty pointers
		if (it->expired())
		{
			it->reset();
			it = objects.erase(it);
			continue;
		}

		// remove if object isn't foundation
		if (dynamic_cast<FoundationBase *>(*it->lock()) == nullptr)
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

Shape FoundationTriangle::GetShape(AimTestResult res)
{
	auto v = vec2(0, m_Height * 2 / 3 - 2);

	std::vector<vec3> points = {
		vec3(v.Transform(mat4::RotationMatrix(0))),
		vec3(v.Transform(mat4::RotationMatrix(120))),
		vec3(v.Transform(mat4::RotationMatrix(-120))),
	};

	mat4 mat = mat4::RotationMatrix(-90 - res.m_Angle) *
			   mat4::TranslateMatrix(res.m_Origin);

	for (size_t i = 0; i < points.size(); i++)
	{
		points[i] = points[i].Transform(mat);
	}

	return Shape(points);
}