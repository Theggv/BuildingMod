#include "Foundation.h"

#include <game/BuildSystem/BuildObjects/Components/OwnerComponent.h>
#include <game/BuildSystem/BuildObjects/Components/RendererComponent.h>
#include <game/BuildSystem/BuildObjects/Components/IColliderComponent.h>
#include <game/BuildSystem/BuildObjects/Components/StabilityComponent.h>

#include <game/Utility/Utility.h>
#include <game/Server/PrecacheManager.h>

Foundation::Foundation(edict_t *owner)
{
	AddComponent(new OwnerComponent(owner));
}

void Foundation::Start()
{
	GameObject::Start();

	auto renderer = new RendererComponent;
	renderer->SetModel(PrecacheManager::Instance().GetFoundationModel());

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

void Foundation::Update()
{
	GameObject::Update();

	if (m_State != BuildState::STATE_SOLID)
	{
		AimPointHandler();
	}
}

void Foundation::StateUpdated()
{
	GameObject::StateUpdated();

	// Update Connections

	if (GetState() != BuildState::STATE_SOLID)
		return;

	vec2 up = GetConnectionPoint(this, FoundationZones::UP, HeightZones::MIDDLE).Round();
	vec2 right = GetConnectionPoint(this, FoundationZones::RIGHT, HeightZones::MIDDLE).Round();
	vec2 down = GetConnectionPoint(this, FoundationZones::DOWN, HeightZones::MIDDLE).Round();
	vec2 left = GetConnectionPoint(this, FoundationZones::LEFT, HeightZones::MIDDLE).Round();

	auto objects = ObjectManager::Instance().GetObjectsInArea(
		(vec3)*GetTransform()->GetPosition());

	for (auto object : objects)
	{
		if (object.empty() || object.expired())
			continue;

		auto foundation = dynamic_cast<Foundation *>(*object.lock());

		if (!foundation)
		{
			object.reset();
			continue;
		}

		vec2 pos = vec2((vec3)*foundation->GetTransform()->GetPosition()).Round();

		if (pos == up)
		{
			AddConnection(foundation, FoundationZones::UP);
			foundation->AddConnection(this, FoundationZones::DOWN);
		}
		else if (pos == right)
		{
			AddConnection(foundation, FoundationZones::RIGHT);
			foundation->AddConnection(this, FoundationZones::LEFT);
		}
		else if (pos == down)
		{
			AddConnection(foundation, FoundationZones::DOWN);
			foundation->AddConnection(this, FoundationZones::UP);
		}
		else if (pos == left)
		{
			AddConnection(foundation, FoundationZones::LEFT);
			foundation->AddConnection(this, FoundationZones::RIGHT);
		}
	}
}

void Foundation::AddConnection(GameObject *object, FoundationZones zone)
{
	// tak ne dolzhno byt', no na vsyakiy sluchay
	if (!m_Connections[static_cast<int>(zone)].empty() &&
		!m_Connections[static_cast<int>(zone)].expired())
		return;

	m_Connections[static_cast<int>(zone)] = ObjectManager::Instance().GetPtr(object->Id);
}

bool Foundation::HasConnection(FoundationZones zone)
{
	if (m_Connections[static_cast<int>(zone)].empty() ||
		m_Connections[static_cast<int>(zone)].expired())
		return false;

	return true;
}

void Foundation::AimPointHandler()
{
	auto owner = GetComponent<OwnerComponent>()->GetOwner();
	auto ownerOrigin = owner->v.origin;

	auto viewPoint = UTIL_GetEndPoint(ENTINDEX(owner), 300.0f);
	viewPoint.z += m_MinHeight;

	auto aimRay = ray(vec3(ownerOrigin),
					  (vec3(viewPoint) - vec3(ownerOrigin)),
					  500.0);

	bool isAimTestPassed = FoundationAimTest(aimRay, vec3(ownerOrigin));

	bool isTestPassed = TraceGroundTest(viewPoint, owner->v.v_angle);

	TrySetState(isTestPassed ? BuildState::STATE_CAN_BUILD : BuildState::STATE_CANNOT_BUILD);

	if (!isAimTestPassed)
	{
		GetTransform()->GetPosition()->setVector(viewPoint.x, viewPoint.y, viewPoint.z);
		GetTransform()->GetRotation()->y(owner->v.v_angle.y);
	}
}

/**
 * BUG: Если фундамент прикреплен к другому, фикс высоты не сработает
 * */
bool Foundation::TraceGroundTest(Vector &viewPoint, Vector &viewAngle)
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

	auto mat = mat4::RotationMatrix(-viewAngle.y) *
			   mat4::TranslateMatrix((vec3)viewPoint);

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
		return true;

	if (maxHeight <= 150)
	{
		viewPoint.z = viewPoint.z - maxHeight + m_MaxHeight;

		return TraceGroundTest(viewPoint, viewAngle);
	}

	return false;
}

bool Foundation::FoundationAimTest(ray &ray, vec3 &ownerOrigin)
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

		auto gameObject = dynamic_cast<Foundation *>(*it->lock());

		// remove if object isn't foundation
		if (gameObject == nullptr)
		{
			it->reset();
			it = objects.erase(it);
			continue;
		}

		++it;
	}

	if (!objects.size())
		return false;

	sort(objects.begin(), objects.end(), [&ownerOrigin](const p_GameObjectWeak_t a_ptr, const p_GameObjectWeak_t b_ptr) {
		vec3 posA = *(*a_ptr.lock())->GetTransform()->GetPosition();
		vec3 posB = *(*b_ptr.lock())->GetTransform()->GetPosition();

		auto distVec1 = posA - ownerOrigin;
		auto distVec2 = posB - ownerOrigin;

		return distVec1.LengthSquared() < distVec2.LengthSquared();
	});

	// for (auto obj : objects)
	// {
	// 	auto gameObject = *obj.lock();

	// 	auto dist = (static_cast<vec3>(*gameObject->GetTransform()->GetPosition()) - ownerOrigin).Length();

	// 	SEM_PRINT("[Building Mod] Distance to object #%d = %.2f", gameObject->Id, dist);
	// }

	// SEM_PRINT("[Building Mod] --------------------------------------------");

	for (auto object_p : objects)
	{
		auto foundation = dynamic_cast<Foundation *>(*object_p.lock());
		auto result = FoundationConnectionTest(ray, foundation);

		if (result != -1)
		{
			// SEM_PRINT("[Building Mod] Height: %d, Zone: %d", result >> 4, result & 3);

			vec3 pos = GetConnectionPoint(
				foundation,
				static_cast<FoundationZones>(result & 3),
				static_cast<HeightZones>(result >> 4));

			vec3 rot = *foundation->GetTransform()->GetRotation();

			GetTransform()->GetPosition()->setVector(pos.x, pos.y, pos.z);
			GetTransform()->GetRotation()->y(rot.y);

			return true;
		}
	}

	return false;
}

/**
 * LOW | MEDIUM | HIGH 			(0 | 1 | 2) << 4
 * UP | RIGHT | DOWN | LEFT 	(0 | 1 | 2 | 3)
 * */
int Foundation::FoundationConnectionTest(ray &ray, Foundation *other)
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
				static_cast<FoundationZones>(zone),
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

	return minZone;
}

std::vector<Triangle> Foundation::GetTriggerZone(FoundationZones zone, HeightZones height)
{
	// basic impl, without zones check
	std::vector<Triangle> triangles;
	std::vector<Triangle> buffer;

	// Return empty list if zone is not empty
	if (HasConnection(zone))
		return triangles;

	// list of heights
	std::vector<vec2> heights = {vec2(-128, -30), vec2(-30, 30), vec2(30, 128)};

	auto minHeight = heights[static_cast<int>(height)].x;
	auto maxHeight = heights[static_cast<int>(height)].y;

	auto hasUp = HasConnection(FoundationZones::UP);
	auto hasRight = HasConnection(FoundationZones::RIGHT);
	auto hasDown = HasConnection(FoundationZones::DOWN);
	auto hasLeft = HasConnection(FoundationZones::LEFT);

	switch (zone)
	{
	case FoundationZones::UP:

		// Bottom side (const)
		buffer = Shape({vec3(-m_ModelSize / 2, m_ModelSize / 2, minHeight),
						vec3(-m_ModelSize / 2, m_ModelSize / 2, maxHeight),
						vec3(m_ModelSize / 2, m_ModelSize / 2, maxHeight),
						vec3(m_ModelSize / 2, m_ModelSize / 2, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		// Left side
		buffer = Shape({vec3(-m_ModelSize / 2, m_ModelSize / 2, minHeight),
						vec3(-m_ModelSize / 2, m_ModelSize / 2, maxHeight),
						vec3(hasLeft ? -m_ModelSize / 2 : -m_ModelSize, m_ModelSize, maxHeight),
						vec3(hasLeft ? -m_ModelSize / 2 : -m_ModelSize, m_ModelSize, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		// Right side
		buffer = Shape({vec3(-m_ModelSize / 2, m_ModelSize / 2, minHeight),
						vec3(-m_ModelSize / 2, m_ModelSize / 2, maxHeight),
						vec3(hasRight ? m_ModelSize / 2 : m_ModelSize, m_ModelSize, maxHeight),
						vec3(hasRight ? m_ModelSize / 2 : m_ModelSize, m_ModelSize, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		// Top side
		buffer = Shape({vec3(hasLeft ? -m_ModelSize / 2 : -m_ModelSize, m_ModelSize, minHeight),
						vec3(hasLeft ? -m_ModelSize / 2 : -m_ModelSize, m_ModelSize, maxHeight),
						vec3(hasRight ? m_ModelSize / 2 : m_ModelSize, m_ModelSize, maxHeight),
						vec3(hasRight ? m_ModelSize / 2 : m_ModelSize, m_ModelSize, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		break;
	case FoundationZones::RIGHT:

		// Left side (const)
		buffer = Shape({vec3(m_ModelSize / 2, m_ModelSize / 2, minHeight),
						vec3(m_ModelSize / 2, m_ModelSize / 2, maxHeight),
						vec3(m_ModelSize / 2, -m_ModelSize / 2, maxHeight),
						vec3(m_ModelSize / 2, -m_ModelSize / 2, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		// Top side
		buffer = Shape({vec3(m_ModelSize / 2, m_ModelSize / 2, minHeight),
						vec3(m_ModelSize / 2, m_ModelSize / 2, maxHeight),
						vec3(m_ModelSize, hasUp ? m_ModelSize / 2 : m_ModelSize, maxHeight),
						vec3(m_ModelSize, hasUp ? m_ModelSize / 2 : m_ModelSize, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		// Bottom side
		buffer = Shape({vec3(m_ModelSize / 2, -m_ModelSize / 2, minHeight),
						vec3(m_ModelSize / 2, -m_ModelSize / 2, maxHeight),
						vec3(m_ModelSize, hasUp ? -m_ModelSize / 2 : -m_ModelSize, maxHeight),
						vec3(m_ModelSize, hasUp ? -m_ModelSize / 2 : -m_ModelSize, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		// Right side
		buffer = Shape({vec3(m_ModelSize, hasUp ? m_ModelSize / 2 : m_ModelSize, minHeight),
						vec3(m_ModelSize, hasUp ? m_ModelSize / 2 : m_ModelSize, maxHeight),
						vec3(m_ModelSize, hasDown ? -m_ModelSize / 2 : -m_ModelSize, maxHeight),
						vec3(m_ModelSize, hasDown ? -m_ModelSize / 2 : -m_ModelSize, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		break;
	case FoundationZones::DOWN:
		// Top side (const)
		buffer = Shape({vec3(-m_ModelSize / 2, -m_ModelSize / 2, minHeight),
						vec3(-m_ModelSize / 2, -m_ModelSize / 2, maxHeight),
						vec3(m_ModelSize / 2, -m_ModelSize / 2, maxHeight),
						vec3(m_ModelSize / 2, -m_ModelSize / 2, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		// Left side
		buffer = Shape({vec3(-m_ModelSize / 2, -m_ModelSize / 2, minHeight),
						vec3(-m_ModelSize / 2, -m_ModelSize / 2, maxHeight),
						vec3(hasLeft ? -m_ModelSize / 2 : -m_ModelSize, -m_ModelSize, maxHeight),
						vec3(hasLeft ? -m_ModelSize / 2 : -m_ModelSize, -m_ModelSize, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		// Right side
		buffer = Shape({vec3(-m_ModelSize / 2, -m_ModelSize / 2, minHeight),
						vec3(-m_ModelSize / 2, -m_ModelSize / 2, maxHeight),
						vec3(hasRight ? m_ModelSize / 2 : m_ModelSize, -m_ModelSize, maxHeight),
						vec3(hasRight ? m_ModelSize / 2 : m_ModelSize, -m_ModelSize, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		// Bottom side
		buffer = Shape({vec3(hasLeft ? -m_ModelSize / 2 : -m_ModelSize, -m_ModelSize, minHeight),
						vec3(hasLeft ? -m_ModelSize / 2 : -m_ModelSize, -m_ModelSize, maxHeight),
						vec3(hasRight ? m_ModelSize / 2 : m_ModelSize, -m_ModelSize, maxHeight),
						vec3(hasRight ? m_ModelSize / 2 : m_ModelSize, -m_ModelSize, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		break;
	case FoundationZones::LEFT:

		// Right side (const)
		buffer = Shape({vec3(-m_ModelSize / 2, m_ModelSize / 2, minHeight),
						vec3(-m_ModelSize / 2, m_ModelSize / 2, maxHeight),
						vec3(-m_ModelSize / 2, -m_ModelSize / 2, maxHeight),
						vec3(-m_ModelSize / 2, -m_ModelSize / 2, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		// Top side
		buffer = Shape({vec3(-m_ModelSize / 2, m_ModelSize / 2, minHeight),
						vec3(-m_ModelSize / 2, m_ModelSize / 2, maxHeight),
						vec3(-m_ModelSize, hasUp ? m_ModelSize / 2 : m_ModelSize, maxHeight),
						vec3(-m_ModelSize, hasUp ? m_ModelSize / 2 : m_ModelSize, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		// Bottom side
		buffer = Shape({vec3(-m_ModelSize / 2, -m_ModelSize / 2, minHeight),
						vec3(-m_ModelSize / 2, -m_ModelSize / 2, maxHeight),
						vec3(-m_ModelSize, hasUp ? -m_ModelSize / 2 : -m_ModelSize, maxHeight),
						vec3(-m_ModelSize, hasUp ? -m_ModelSize / 2 : -m_ModelSize, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		// Left side
		buffer = Shape({vec3(-m_ModelSize, hasUp ? m_ModelSize / 2 : m_ModelSize, minHeight),
						vec3(-m_ModelSize, hasUp ? m_ModelSize / 2 : m_ModelSize, maxHeight),
						vec3(-m_ModelSize, hasDown ? -m_ModelSize / 2 : -m_ModelSize, maxHeight),
						vec3(-m_ModelSize, hasDown ? -m_ModelSize / 2 : -m_ModelSize, minHeight)})
					 .Triangulate();
		triangles.insert(triangles.end(), buffer.begin(), buffer.end());

		break;
	}

	// Transform
	vec3 pos = *GetTransform()->GetPosition();
	vec3 rot = *GetTransform()->GetRotation();

	mat4 mat = mat4::RotationMatrix(-rot.y) *
			   mat4::TranslateMatrix(pos);

	for (auto &triangle : triangles)
	{
		triangle.Transform(mat);
	}

	return triangles;
}

vec3 Foundation::GetConnectionPoint(
	Foundation *foundation, FoundationZones foundationZone, HeightZones heightZone)
{
	double heights[3] = {-foundation->m_ModelSize / 2.0, 0, foundation->m_ModelSize / 2.0};
	auto height = heights[static_cast<int>(heightZone)];

	vec3 newPos;

	switch (foundationZone)
	{
	case FoundationZones::UP:
		newPos = vec3(0, foundation->m_ModelSize, height);
		break;
	case FoundationZones::RIGHT:
		newPos = vec3(foundation->m_ModelSize, 0, height);
		break;
	case FoundationZones::DOWN:
		newPos = vec3(0, -foundation->m_ModelSize, height);
		break;
	case FoundationZones::LEFT:
		newPos = vec3(-foundation->m_ModelSize, 0, height);
		break;
	}

	vec3 pos = *foundation->GetTransform()->GetPosition();
	vec3 rot = *foundation->GetTransform()->GetRotation();

	mat4 mat = mat4::RotationMatrix(-rot.y) *
			   mat4::TranslateMatrix(pos);

	return newPos.Transform(mat);
}
