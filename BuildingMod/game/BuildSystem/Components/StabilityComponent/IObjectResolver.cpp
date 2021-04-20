#include "IObjectResolver.h"
#include "IConnectionPoints.h"
#include "../IStabilityComponent.h"

IObjectResolver::~IObjectResolver()
{
	delete m_Successor;
	delete m_Handler;
}

void IObjectResolver::SetSuccessor(IObjectResolver *successor)
{
	m_Successor = successor;
}

void IObjectResolver::AddConnection(
	GameObject *object,
	GameObject *bindable)
{
	if (!CanResolve(object, bindable))
	{
		if (m_Successor != nullptr)
			m_Successor->AddConnection(object, bindable);

		return;
	}

	auto zoneId = m_Handler->GetZoneIdByPosition(
		object,
		bindable,
		*bindable->GetTransform()->GetPosition());

	if (zoneId < 0)
		return;

	auto type = m_Handler->GetTypeByZone(zoneId);

	if (m_Connections.find(zoneId) != m_Connections.end())
	{
		m_Connections[zoneId] = ObjectManager::Instance().GetPtr(bindable->Id);
	}
	else
	{
		m_Connections.insert(
			{zoneId, ObjectManager::Instance().GetPtr(bindable->Id)});
	}

	GenerateZones();
}

bool IObjectResolver::HasConnection(
	GameObject *object,
	GameObject *bindable,
	vec3 pos)
{
	if (!CanResolve(object, bindable))
	{
		if (m_Successor != nullptr)
			return m_Successor->HasConnection(object, bindable, pos);
	}

	auto zoneId = m_Handler->GetZoneIdByPosition(
		object,
		bindable, pos);

	return HasConnection(zoneId);
}

bool IObjectResolver::HasConnection(int zoneId)
{
	if (zoneId < 0)
		return false;

	if (m_Connections.find(zoneId) != m_Connections.end())
	{
		return !m_Connections[zoneId].empty() &&
			   !m_Connections[zoneId].expired();
	}

	return false;
}

void IObjectResolver::RemoveConnection(GameObject *object, GameObject *bindable)
{
	if (!CanResolve(object, bindable))
	{
		if (m_Successor != nullptr)
			m_Successor->RemoveConnection(object, bindable);

		return;
	}

	auto zoneId = m_Handler->GetZoneIdByPosition(
		object,
		bindable,
		*bindable->GetTransform()->GetPosition());

	if (zoneId < 0)
		return;

	if (m_Connections.find(zoneId) != m_Connections.end())
	{
		m_Connections.erase(zoneId);
	}

	GenerateZones();
}

void IObjectResolver::RemoveConnections(GameObject *object)
{
	for (auto connection : m_Connections)
	{
		auto object_p = connection.second;

		if (object_p.empty() || object_p.expired())
			continue;

		auto other = *object_p.lock();

		auto stability = other->GetComponent<IStabilityComponent>();

		if (stability == nullptr)
			continue;

		stability->RemoveConnection(object);
	}
}

vector<Connection> IObjectResolver::GetConnections()
{
	throw exception("Not implemented");
	// vector<Connection> connections;
	// IObjectResolver *resolver = this;

	// do
	// {
	// 	for (auto connection : resolver->m_Connections)
	// 	{
	// 		connections.push_back(connection.second);
	// 	}

	// 	resolver = resolver->m_Successor;

	// } while (resolver != nullptr);

	// return connections;
}

AimTestResult IObjectResolver::TryConnect(ray ray, GameObject *object, GameObject *bindable)
{
	if (!CanResolve(object, bindable))
		return CallNext(ray, object, bindable);

	vec3 hit;
	bool intersection;

	int minRayLength = 75;
	bool minLengthTest;

	int minZone = -1;
	double minLengthSquared = 0;
	double curLengthSquared;

	for (size_t zoneId = 0; zoneId < m_Zones.size(); zoneId++)
	{
		auto transformedZone = GetTransformedZone(object, zoneId);

		for (auto triangle : transformedZone)
		{
			intersection = triangle.RayIntersection(ray, hit);

			if (!intersection)
				continue;

			curLengthSquared = (hit - ray.GetOrigin()).LengthSquared();
			minLengthTest = curLengthSquared >= minRayLength * minRayLength;

			if (!minLengthTest)
				continue;

			if (!minLengthSquared || curLengthSquared < minLengthSquared)
			{
				minLengthSquared = curLengthSquared;
				minZone = zoneId;
			}
		}
	}

	if (minZone == -1)
		return AimTestResult(false);

	// if (m_Visualizer != nullptr)
	// {
	//     if (!m_Visualizer->IsEnabled())
	//         m_Visualizer->Enable();

	//     m_Visualizer->Visualize(GetTransformedZone(object, minZone));
	// }

	return m_Handler->GetConnectionPoint(object, bindable, minZone);
}

vector<Triangle> IObjectResolver::GetTransformedZone(GameObject *object, int zoneId)
{
	vector<Triangle> tries;

	// Transform
	vec3 pos = *object->GetTransform()->GetPosition();
	vec3 rot = *object->GetTransform()->GetRotation();

	mat4 mat = mat4::RotationMatrix(90 - rot.y) *
			   mat4::TranslateMatrix(pos);

	for (auto &triangle : m_Zones[zoneId])
	{
		tries.push_back(triangle.Transform(mat));
	}

	return tries;
}

AimTestResult IObjectResolver::CallNext(ray ray, GameObject *object, GameObject *bindable)
{
	if (m_Successor != nullptr)
		return m_Successor->TryConnect(ray, object, bindable);

	return AimTestResult(false);
}
