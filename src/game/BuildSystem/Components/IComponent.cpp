#include "IComponent.h"
#include <game/BuildSystem/ObjectManager.h>

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
	m_Parent = ObjectManager::Instance().GetPtr(parent->Id);
}

p_GameObject_t IComponent::GetParent()
{
	if (m_Parent.expired())
		return nullptr;

	return m_Parent.lock();
}

void IComponent::SetValid(bool isValid)
{
	m_IsValid = false;
}
