#include "IStabilityComponent.h"
#include <game/BuildSystem/ConnectionManager.h>

IStabilityComponent::IStabilityComponent()
{
	m_Stability = 0;
}

IStabilityComponent::~IStabilityComponent()
{
	delete m_ObjectResolver;
}

void IStabilityComponent::OnStateUpdated()
{
	IComponent::OnStateUpdated();

	if (m_Parent->GetState() != BuildState::STATE_SOLID)
		return;

	CalculateStability();
}

void IStabilityComponent::UpdateDependentObjects(int cycle)
{
	// prevent random loop recursion
	if (cycle >= 100)
		return;

	// Update dependent objects
	auto links = ConnectionManager::Instance().GetAllLinks(m_Parent);

	for (auto link : links)
	{
		// All links should be valid, but check for safety
		if (link.ptr.expired())
			continue;

		if (link.type == ConnectionTypes::Additional ||
			link.type == ConnectionTypes::Child)
		{
			auto object = *link.ptr.lock();

			auto stability = object->GetComponent<IStabilityComponent>();

			// Check is object has stability component, for safety ofc
			if (stability == nullptr)
				continue;

			stability->CalculateStability(cycle + 1);
		}
	}
}

double IStabilityComponent::GetStability()
{
	return m_Stability;
}

AimTestResult IStabilityComponent::TryConnect(ray ray, GameObject *object)
{
	return m_ObjectResolver->TryConnect(ray, m_Parent, object);
}

void IStabilityComponent::AddConnection(GameObject *object)
{
	m_ObjectResolver->AddConnection(m_Parent, object);
}

void IStabilityComponent::RemoveConnection(GameObject *object)
{
	m_ObjectResolver->RemoveConnection(m_Parent, object);
}

set<Connection, ConnectionOrdering> IStabilityComponent::GetConnections()
{
	return ConnectionManager::Instance().GetAllLinks(m_Parent);
	// return m_ObjectResolver->GetConnections();
}
