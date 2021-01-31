#include "FoundationTriangle.h"

#include "TriangleCollider.h"

#include <game/BuildSystem/BuildObjects/Components/OwnerComponent.h>
#include <game/BuildSystem/BuildObjects/Components/RendererComponent.h>
#include <game/BuildSystem/BuildObjects/Components/IColliderComponent.h>
#include <game/BuildSystem/BuildObjects/Components/VisualizerComponent.h>

#include <game/BuildSystem/BuildObjects/FoundationSquare/FoundationSquare.h>

#include <game/Utility/Utility.h>
#include <game/Server/PrecacheManager.h>

const double FoundationTriangle::m_Height = m_ModelSize * sin(60 * M_PI / 180);

FoundationTriangle::FoundationTriangle(edict_t *owner) : FoundationBase(owner)
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

AimTestResult FoundationTriangle::TraceGroundTest(AimTestResult result)
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
		result.m_Origin.z = result.m_Origin.z - maxHeight + m_MaxHeight;

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
		auto foundation = dynamic_cast<FoundationBase *>(*object_p.lock());
		auto foundationSquare = dynamic_cast<FoundationSquare *>(*object_p.lock());
		auto foundationTriangle = dynamic_cast<FoundationTriangle *>(*object_p.lock());

		int result = -1;

		if (foundationSquare != nullptr)
			result = FoundationConnectionTest(ray, foundationSquare);
		else if (foundationTriangle != nullptr)
			result = FoundationConnectionTest(ray, foundationTriangle);

		if (result == -1)
			continue;

		vec3 pos = vec3::Zero();
		vec3 rot = *foundation->GetTransform()->GetRotation();

		// SEM_PRINT("[Building Mod] Height: %d, Zone: %d, angle: %.1f",
		// 		  result >> 4, result & 3, rot.y);

		if (foundationSquare != nullptr)
		{
			vec3 pos = foundationSquare->GetConnectionPoint(
				static_cast<SquareZones>(result & 3),
				static_cast<HeightZones>(result >> 4), true);

			switch (static_cast<SquareZones>(result & 3))
			{
			case SquareZones::RIGHT:
				return AimTestResult(true, pos, rot.y - 90);

			case SquareZones::DOWN:
				return AimTestResult(true, pos, rot.y + 180);

			case SquareZones::LEFT:
				return AimTestResult(true, pos, rot.y + 90);

			case SquareZones::UP:
				return AimTestResult(true, pos, rot.y);
			}
		}
		else if (foundationTriangle != nullptr)
		{
			vec3 pos = foundationTriangle->GetConnectionPoint(
				static_cast<TriangleZones>(result & 3),
				static_cast<HeightZones>(result >> 4), true);

			switch (static_cast<TriangleZones>(result & 3))
			{
			case TriangleZones::RIGHT:
				return AimTestResult(true, pos, rot.y + 60 + 180);

			case TriangleZones::DOWN:
				return AimTestResult(true, pos, rot.y + 180 + 180);

			case TriangleZones::LEFT:
				return AimTestResult(true, pos, rot.y - 60 + 180);
			}
		}
	}

	return AimTestResult(false, ray.GetDest(), ray.GetVectorAngle());
}

void FoundationTriangle::AddConnection(GameObject *object, TriangleZones zone)
{
	// tak ne dolzhno byt', no na vsyakiy sluchay
	if (!m_Connections[static_cast<int>(zone)].empty() &&
		!m_Connections[static_cast<int>(zone)].expired())
		return;

	m_Connections[static_cast<int>(zone)] = ObjectManager::Instance().GetPtr(object->Id);
}

bool FoundationTriangle::HasConnection(TriangleZones zone)
{
	if (m_Connections[static_cast<int>(zone)].empty() ||
		m_Connections[static_cast<int>(zone)].expired())
		return false;

	return true;
}

void FoundationTriangle::ConnectFoundations(FoundationBase *other, bool useRecursion)
{
	bool isTriangle = dynamic_cast<FoundationSquare *>(other) == nullptr;

	vec2 pos = vec2(*other->GetTransform()->GetPosition()).Round();

	for (size_t i = 0; i < 3; i++)
	{
		vec2 point = GetConnectionPoint(
						 static_cast<TriangleZones>(i), HeightZones::MIDDLE, isTriangle)
						 .Round();

		if (point == pos)
		{
			AddConnection(other, static_cast<TriangleZones>(i));

			if (useRecursion)
				other->ConnectFoundations(this, false);

			return;
		}
	}
}

/**
 * LOW | MEDIUM | HIGH 			(0 | 1 | 2) << 4
 * UP | RIGHT | DOWN | LEFT 	(0 | 1 | 2 | 3)
 * */
int FoundationTriangle::FoundationConnectionTest(ray ray, FoundationSquare *other)
{
	// auto stability = other->GetComponent<StabilityComponent *>();
	vec3 hit;
	bool intersection;

	int minRayLength = 75;
	bool minLengthTest;

	int minZone = -1;
	double minLengthSquared = 0;
	double curLengthSquared;

	for (size_t height = 0; height < 3; ++height)
	{
		for (size_t zone = 0; zone < 4; zone++)
		{
			auto triangles = other->GetTriggerZone(
				static_cast<SquareZones>(zone),
				static_cast<HeightZones>(height));

			for (auto triangle : triangles)
			{
				intersection = triangle.RayIntersection(ray, hit);
				curLengthSquared = (hit - ray.GetOrigin()).LengthSquared();
				minLengthTest = curLengthSquared >= minRayLength * minRayLength;

				if (intersection && minLengthTest)
				{
					if (!minLengthSquared || curLengthSquared < minLengthSquared)
					{
						minLengthSquared = curLengthSquared;
						minZone = (height << 4) + zone;
					}
				}
			}
		}
	}

	if (minZone != -1)
	{
		auto tries = other->GetTriggerZone(
			static_cast<SquareZones>(minZone & 3),
			static_cast<HeightZones>(minZone >> 4));

		GetComponent<VisualizerComponent>()->Visualize(tries);
	}

	return minZone;
}

/**
 * LOW | MEDIUM | HIGH 			(0 | 1 | 2) << 4
 * RIGHT | DOWN | LEFT 	(0 | 1 | 2 | 3)
 * */
int FoundationTriangle::FoundationConnectionTest(ray ray, FoundationTriangle *other)
{
	vec3 hit;
	bool intersection;

	int minRayLength = 75;
	bool minLengthTest;

	int minZone = -1;
	double minLengthSquared = 0;
	double curLengthSquared;

	for (size_t height = 0; height < 3; ++height)
	{
		for (size_t zone = 0; zone < 3; zone++)
		{
			auto triangles = other->GetTriggerZone(
				static_cast<TriangleZones>(zone),
				static_cast<HeightZones>(height));

			for (auto triangle : triangles)
			{
				intersection = triangle.RayIntersection(ray, hit);
				curLengthSquared = (hit - ray.GetOrigin()).LengthSquared();
				minLengthTest = curLengthSquared >= minRayLength * minRayLength;

				if (intersection && minLengthTest)
				{
					if (!minLengthSquared || curLengthSquared < minLengthSquared)
					{
						minLengthSquared = curLengthSquared;
						minZone = (height << 4) + zone;
					}
				}
			}
		}
	}

	if (minZone != -1)
	{
		auto tries = other->GetTriggerZone(
			static_cast<TriangleZones>(minZone & 3),
			static_cast<HeightZones>(minZone >> 4));

		GetComponent<VisualizerComponent>()->Visualize(tries);
	}

	return minZone;
}

std::vector<Triangle> FoundationTriangle::GetTriggerZone(TriangleZones zone, HeightZones height)
{
	// basic impl, without zones check
	std::vector<Triangle> triangles;
	std::vector<Triangle> buffer;

	// Return empty list if zone is not empty
	if (HasConnection(zone))
		return triangles;

	// list of heights (min, max)
	std::vector<vec2> heights = {vec2(-128, -30), vec2(-30, 30), vec2(30, 128)};

	auto hasRight = HasConnection(TriangleZones::RIGHT);
	auto hasDown = HasConnection(TriangleZones::DOWN);
	auto hasLeft = HasConnection(TriangleZones::LEFT);

	// smari shemu, down

	auto a = vec2(0, 2 * m_Height / 3);
	auto b = a.Transform(mat4::RotationMatrix(-120));
	auto c = a.Transform(mat4::RotationMatrix(120));

	auto d = vec2(0, 5 * m_Height / 3);
	auto e = d.Transform(mat4::RotationMatrix(-120));
	auto f = d.Transform(mat4::RotationMatrix(120));

	auto tempVector = vec2(0, ((d - a) / 2).Length() / (sin(60 * M_PI / 180)));

	auto aRight = a + tempVector.Transform(mat4::RotationMatrix(-30));
	auto aLeft = a + tempVector.Transform(mat4::RotationMatrix(30));

	auto bRight = b + tempVector.Transform(mat4::RotationMatrix(-90));
	auto bDown = b + tempVector.Transform(mat4::RotationMatrix(-150));

	auto cLeft = c + tempVector.Transform(mat4::RotationMatrix(90));
	auto cDown = c + tempVector.Transform(mat4::RotationMatrix(150));

	switch (zone)
	{
	case TriangleZones::RIGHT:

		triangles = Triangle::GenerateTriangles(
			a,
			hasLeft ? aRight : d,
			hasDown ? bRight : e,
			b,
			heights[static_cast<int>(height)]);

		break;

	case TriangleZones::DOWN:

		triangles = Triangle::GenerateTriangles(
			b,
			hasRight ? bDown : e,
			hasLeft ? cDown : f,
			c,
			heights[static_cast<int>(height)]);

		break;

	case TriangleZones::LEFT:

		triangles = Triangle::GenerateTriangles(
			c,
			hasDown ? cLeft : f,
			hasRight ? aLeft : d,
			a,
			heights[static_cast<int>(height)]);

		break;
	}

	// Transform
	vec3 pos = *GetTransform()->GetPosition();
	vec3 rot = *GetTransform()->GetRotation();

	mat4 mat = mat4::RotationMatrix(-90 - rot.y) *
			   mat4::TranslateMatrix(pos);

	for (auto &triangle : triangles)
	{
		triangle.Transform(mat);
	}

	return triangles;
}

vec3 FoundationTriangle::GetConnectionPoint(
	TriangleZones zone, HeightZones heightZone, bool isForTriangle)
{
	double heights[3] = {-m_ModelSize / 2.0, 0, m_ModelSize / 2.0};
	auto height = heights[static_cast<int>(heightZone)];

	vec3 newPos = vec3(
		0,
		isForTriangle
			? m_Height * 2 / 3
			: m_ModelSize / 2 + FoundationTriangle::m_Height / 3,
		height);

	switch (zone)
	{
	case TriangleZones::RIGHT:
		newPos = newPos.Transform(mat4::RotationMatrix(-60.0));
		break;
	case TriangleZones::DOWN:
		newPos = newPos.Transform(mat4::RotationMatrix(180.0));
		break;
	case TriangleZones::LEFT:
		newPos = newPos.Transform(mat4::RotationMatrix(60.0));
		break;
	}

	vec3 pos = *GetTransform()->GetPosition();
	vec3 rot = *GetTransform()->GetRotation();

	mat4 mat = mat4::RotationMatrix(-90 - rot.y) *
			   mat4::TranslateMatrix(pos);

	return newPos.Transform(mat);
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