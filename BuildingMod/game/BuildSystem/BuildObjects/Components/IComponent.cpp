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
	m_parent = parent;
}

GameObject* IComponent::GetParent()
{
	return m_parent;
}
