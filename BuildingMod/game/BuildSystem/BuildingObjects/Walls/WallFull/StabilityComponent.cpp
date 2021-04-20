#include "StabilityComponent.h"

// Object resolvers
#include "Resolvers/Wall/WallResolver.h"

using namespace WallFullResolvers;

StabilityComponent::StabilityComponent()
{
    auto wallResolver = new WallResolver;

    m_ObjectResolver = wallResolver;
}

void StabilityComponent::CalculateStability()
{
    m_Stability = 1.0;
}