#include "StabilityComponent.h"

// objects
#include <game/BuildSystem/BuildObjects/FoundationSquare/FoundationSquare.h>
#include <game/BuildSystem/BuildObjects/FoundationTriangle/FoundationTriangle.h>

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