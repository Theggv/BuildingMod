#include "IComponent.h"

IComponent::IComponent()
{
}

IComponent::~IComponent()
{
}

void IComponent::OnStart()
{
}

void IComponent::OnUpdate()
{
}

void IComponent::OnTransformUpdate()
{
}

void IComponent::OnStateUpdated()
{
}

void IComponent::SetParent(GameObject *parent)
{
	m_Parent = parent;
}

GameObject *IComponent::GetParent()
{
	return m_Parent;
}
