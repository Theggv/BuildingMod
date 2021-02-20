#include "IStabilityComponent.h"

IStabilityComponent::IStabilityComponent()
{
    m_Stability = 0;
}

IStabilityComponent::~IStabilityComponent()
{
    delete m_ObjectResolver;
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

bool IStabilityComponent::HasConnection(GameObject *object, vec3 pos)
{
    return m_ObjectResolver->HasConnection(m_Parent, object, pos);
}

void IStabilityComponent::RemoveConnection(GameObject *object)
{
    m_ObjectResolver->RemoveConnection(m_Parent, object);
}