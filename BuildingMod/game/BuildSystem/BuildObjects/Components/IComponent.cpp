#include "IComponent.h"

IComponent::IComponent()
{
	m_ComponentObserver = new ComponentObserver(this);
}

IComponent::~IComponent()
{
	// Detach observer from previous parent if it exists
	if (m_parent)
		m_parent->Transform.Detach(m_ComponentObserver);

	delete m_ComponentObserver;
}

void IComponent::Start()
{
}

void IComponent::Update()
{
}

void IComponent::UpdateTransform()
{
}

void IComponent::Dispose()
{
}

/// <summary>
/// Set parent of component. 
/// </summary>
/// <param name="parent"></param>
void IComponent::SetParent(GameObject* parent)
{
	// Detach observer from previous parent if it exists
	if (m_parent)
		m_parent->Transform.Detach(m_ComponentObserver);

	m_parent = parent;

	// Attach observer to new parent
	m_parent->Transform.Attach(m_ComponentObserver);
}

GameObject* IComponent::GetParent()
{
	return m_parent;
}

IComponent::ComponentObserver::ComponentObserver(IComponent* component) : m_IComponent(component) {}

IComponent::ComponentObserver::~ComponentObserver() {}

void IComponent::ComponentObserver::Update()
{
	m_IComponent->UpdateTransform();
}
