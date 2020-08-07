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

void IComponent::StateUpdated()
{

}

void IComponent::SetParent(GameObject* parent)
{
	m_parent = parent;
}

GameObject* IComponent::GetParent()
{
	return m_parent;
}
