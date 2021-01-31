#include "FoundationSquare.h"

#include <game/BuildSystem/BuildObjects/Components/OwnerComponent.h>
#include <game/BuildSystem/BuildObjects/Components/RendererComponent.h>
#include <game/BuildSystem/BuildObjects/Components/IColliderComponent.h>
#include <game/BuildSystem/BuildObjects/Components/StabilityComponent.h>
#include <game/BuildSystem/BuildObjects/Components/VisualizerComponent.h>

#include <game/BuildSystem/BuildObjects/FoundationTriangle/FoundationTriangle.h>

#include <game/Utility/Utility.h>
#include <game/Server/PrecacheManager.h>

FoundationSquare::FoundationSquare(edict_t *owner) : FoundationBase(owner)
{
}

void FoundationSquare::Start()
{
	FoundationBase::Start();

	auto renderer = new RendererComponent;
	renderer->SetModel(PrecacheManager::Instance().GetFoundationSquareModel());

	AddComponent(renderer);

	auto collider = new IColliderComponent;
	collider->AddEdict(UTIL_CreateEdict("info_target"), true);

	AddComponent(collider);

	for (auto pEntity : collider->GetEdicts(true))
	{
		auto model = (char *)STRING(UTIL_AllocString(renderer->GetModel()));
		SET_MODEL(pEntity, model);
	}

	auto stability = new StabilityComponent;
	AddComponent(stability);
}

void FoundationSquare::StateUpdated()
{
	FoundationBase::StateUpdated();
}

void FoundationSquare::AddConnection(GameObject *object, SquareZones zone)
{
	// tak ne dolzhno byt', no na vsyakiy sluchay
	if (!m_Connections[static_cast<int>(zone)].empty() &&
		!m_Connections[static_cast<int>(zone)].expired())
		return;

	m_Connections[static_cast<int>(zone)] = ObjectManager::Instance().GetPtr(object->Id);
}

bool FoundationSquare::HasConnection(SquareZones zone)
{
	if (m_Connections[static_cast<int>(zone)].empty() ||
		m_Connections[static_cast<int>(zone)].expired())
		return false;

	return true;
}

void FoundationSquare::ConnectFoundations(FoundationBase *other, bool useRecursion)
{
	bool isTriangle = dynamic_cast<FoundationSquare *>(other) == nullptr;

	vec2 pos = vec2(*other->GetTransform()->GetPosition()).Round();

	for (size_t i = 0; i < 4; i++)
	{
		vec2 point = GetConnectionPoint(
						 static_cast<SquareZones>(i), HeightZones::MIDDLE, isTriangle)
						 .Round();

		if (point == pos)
		{
			AddConnection(other, static_cast<SquareZones>(i));

			if (useRecursion)
				other->ConnectFoundations(this, false);

			return;
		}
	}
}

AimTestResult FoundationSquare::TraceGroundTest(vec3 viewPoint, vec3 viewAngle)
{
	TraceResult tr;

	int numHits = 0;
	vector<vec3> points{
		vec3::Zero(),
		vec3(-40, -40, 0),
		vec3(-40, 40, 0),
		vec3(40, -40, 0),
		vec3(40, 40, 0),
	};

	auto mat = mat4::RotationMatrix(viewAngle.y) *
			   mat4::TranslateMatrix(viewPoint);

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

	if (numHits >= 4)
		return AimTestResult(true, viewPoint);

	if (maxHeight <= 150)
	{
		viewPoint.z = viewPoint.z - maxHeight + m_MaxHeight;

		return TraceGroundTest(viewPoint, viewAngle);
	}

	return AimTestResult(false);
}

AimTestResult FoundationSquare::FoundationAimTest(ray ray)
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
		return AimTestResult(false);

	sort(objects.begin(), objects.end(), [&ray](const p_GameObjectWeak_t a_ptr, const p_GameObjectWeak_t b_ptr) {
		vec3 posA = *(*a_ptr.lock())->GetTransform()->GetPosition();
		vec3 posB = *(*b_ptr.lock())->GetTransform()->GetPosition();

		auto distVec1 = posA - ray.GetOrigin();
		auto distVec2 = posB - ray.GetOrigin();

		return distVec1.LengthSquared() < distVec2.LengthSquared();
	});

	// for (auto obj : objects)
	// {
	// 	auto gameObject = *obj.lock();

	// 	auto dist = (static_cast<vec3>(*gameObject->GetTransform()->GetPosition()) - ray.GetOrigin()).Length();

	// 	SEM_PRINT("[Building Mod] Distance to object #%d = %.2f", gameObject->Id, dist);
	// }

	// SEM_PRINT("[Building Mod] --------------------------------------------");

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
				static_cast<HeightZones>(result >> 4), false);

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
				static_cast<HeightZones>(result >> 4), false);

			switch (static_cast<TriangleZones>(result & 3))
			{
			case TriangleZones::RIGHT:
				return AimTestResult(true, pos, rot.y + 60);

			case TriangleZones::DOWN:
				return AimTestResult(true, pos, rot.y + 180);

			case TriangleZones::LEFT:
				return AimTestResult(true, pos, rot.y - 60);
			}
		}
	}

	return AimTestResult(false);
}

/**
 * LOW | MEDIUM | HIGH 			(0 | 1 | 2) << 4
 * RIGHT | DOWN | LEFT | UP 	(0 | 1 | 2 | 3)
 * */
int FoundationSquare::FoundationConnectionTest(ray ray, FoundationSquare *other)
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
 * RIGHT | DOWN | LEFT 	(0 | 1 | 2)
 * */
int FoundationSquare::FoundationConnectionTest(ray ray, FoundationTriangle *other)
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

std::vector<Triangle> FoundationSquare::GetTriggerZone(SquareZones zone, HeightZones height)
{
	// basic impl, without zones check
	std::vector<Triangle> triangles;
	std::vector<Triangle> buffer;

	// Return empty list if zone is not empty
	if (HasConnection(zone))
		return triangles;

	// list of heights (min, max)
	std::vector<vec2> heights = {vec2(-128, -30), vec2(-30, 30), vec2(30, 128)};

	auto minHeight = heights[static_cast<int>(height)].x;
	auto maxHeight = heights[static_cast<int>(height)].y;

	auto hasRight = HasConnection(SquareZones::RIGHT);
	auto hasDown = HasConnection(SquareZones::DOWN);
	auto hasLeft = HasConnection(SquareZones::LEFT);
	auto hasUp = HasConnection(SquareZones::UP);

	switch (zone)
	{
	case SquareZones::RIGHT:

		// cw
		triangles = GenerateTriangles(
			vec2(m_ModelSize / 2, m_ModelSize / 2),
			hasUp ? vec2(m_ModelSize, m_ModelSize / 2) : vec2(m_ModelSize, m_ModelSize),
			hasDown ? vec2(m_ModelSize, -m_ModelSize / 2) : vec2(m_ModelSize, -m_ModelSize),
			vec2(m_ModelSize / 2, -m_ModelSize / 2),
			heights[static_cast<int>(height)]);

		break;
	case SquareZones::DOWN:

		// cw
		triangles = GenerateTriangles(
			vec2(m_ModelSize / 2, -m_ModelSize / 2),
			hasRight ? vec2(m_ModelSize / 2, -m_ModelSize) : vec2(m_ModelSize, -m_ModelSize),
			hasLeft ? vec2(-m_ModelSize / 2, -m_ModelSize) : vec2(-m_ModelSize, -m_ModelSize),
			vec2(-m_ModelSize / 2, -m_ModelSize / 2),
			heights[static_cast<int>(height)]);

		break;
	case SquareZones::LEFT:

		// cw
		triangles = GenerateTriangles(
			vec2(-m_ModelSize / 2, -m_ModelSize / 2),
			hasDown ? vec2(-m_ModelSize, -m_ModelSize / 2) : vec2(-m_ModelSize, -m_ModelSize),
			hasUp ? vec2(-m_ModelSize, m_ModelSize / 2) : vec2(-m_ModelSize, m_ModelSize),
			vec2(-m_ModelSize / 2, m_ModelSize / 2),
			heights[static_cast<int>(height)]);

		break;
	case SquareZones::UP:

		// cw
		triangles = GenerateTriangles(
			vec2(-m_ModelSize / 2, m_ModelSize / 2),
			hasLeft ? vec2(-m_ModelSize / 2, m_ModelSize) : vec2(-m_ModelSize, m_ModelSize),
			hasRight ? vec2(m_ModelSize / 2, m_ModelSize) : vec2(m_ModelSize, m_ModelSize),
			vec2(m_ModelSize / 2, m_ModelSize / 2),
			heights[static_cast<int>(height)]);

		break;
	}

	// Transform
	vec3 pos = *GetTransform()->GetPosition();
	vec3 rot = *GetTransform()->GetRotation();

	mat4 mat = mat4::RotationMatrix(90 - rot.y) *
			   mat4::TranslateMatrix(pos);

	for (auto &triangle : triangles)
	{
		triangle.Transform(mat);
	}

	return triangles;
}

vec3 FoundationSquare::GetConnectionPoint(
	SquareZones SquareZones, HeightZones heightZone, bool isForTriangle)
{
	double heights[3] = {-m_ModelSize / 2.0, 0, m_ModelSize / 2.0};
	auto height = heights[static_cast<int>(heightZone)];

	vec3 newPos = vec3(
		0,
		isForTriangle
			? m_ModelSize / 2 + FoundationTriangle::m_Height / 3
			: m_ModelSize,
		height);

	switch (SquareZones)
	{
	case SquareZones::RIGHT:
		newPos = newPos.Transform(mat4::RotationMatrix(90));
		break;
	case SquareZones::DOWN:
		newPos = newPos.Transform(mat4::RotationMatrix(180));
		break;
	case SquareZones::LEFT:
		newPos = newPos.Transform(mat4::RotationMatrix(-90));
		break;
	case SquareZones::UP:
		newPos = newPos.Transform(mat4::RotationMatrix(0));
		break;
	}

	vec3 pos = *GetTransform()->GetPosition();
	vec3 rot = *GetTransform()->GetRotation();

	mat4 mat = mat4::RotationMatrix(90 - rot.y) *
			   mat4::TranslateMatrix(pos);

	return newPos.Transform(mat);
}
