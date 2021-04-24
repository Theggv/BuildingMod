#include "IStabilityComponent.h"
#include <game/BuildSystem/ConnectionManager.h>

IStabilityComponent::IStabilityComponent()
{
	m_Stability = 0;
}

IStabilityComponent::~IStabilityComponent()
{
	delete m_ObjectResolver;

	ConnectionManager::Instance().RemoveLinks(GetParent());
}

void IStabilityComponent::OnStateUpdated()
{
	IComponent::OnStateUpdated();

	if (GetParent()->GetState() != BuildState::STATE_SOLID)
		return;

	CalculateStability();
}

void IStabilityComponent::UpdateDependentObjects(int cycle)
{
	if (!m_IsValid)
		return;

	// prevent random loop recursion
	if (cycle >= 100)
		return;

	// Update dependent objects
	auto links = ConnectionManager::Instance().GetAllLinks(GetParent());

	for (auto link : links)
	{
		// All links should be valid, but check for safety
		if (link.ptr.lock() == nullptr)
			continue;

		if (link.type == ConnectionTypes::Additional ||
			link.type == ConnectionTypes::Child)
		{
			auto object = link.ptr.lock();

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

AimTestResult IStabilityComponent::TryConnect(ray ray, p_GameObject_t object)
{
	return m_ObjectResolver->TryConnect(ray, GetParent(), object);
}

void IStabilityComponent::AddConnection(p_GameObject_t object)
{
	m_ObjectResolver->AddConnection(GetParent(), object);
}

void IStabilityComponent::RemoveConnection(p_GameObject_t object)
{
	m_ObjectResolver->RemoveConnection(GetParent(), object);
}

set<Connection, ConnectionOrdering> IStabilityComponent::GetConnections()
{
	return ConnectionManager::Instance().GetAllLinks(GetParent());
}

void IStabilityComponent::OnStabilityCalculated()
{
	if (m_Stability < 0.50)
	{
		ObjectManager::Instance().Remove(GetParent());
	}
}
