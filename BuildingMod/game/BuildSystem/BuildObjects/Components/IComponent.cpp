#include "..\GameObject.h"
#include "IComponent.h"

IComponent::IComponent()
{

}

IComponent::~IComponent()
{

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
