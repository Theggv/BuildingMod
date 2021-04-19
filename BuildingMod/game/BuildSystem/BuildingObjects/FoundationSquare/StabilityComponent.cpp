#include "StabilityComponent.h"

// objects
#include <game/BuildSystem/BuildingObjects/FoundationSquare/FoundationSquare.h>

// Object resolvers
#include "Resolvers/Foundation/FoundationResolver.h"
#include "Resolvers/Wall/WallResolver.h"

using namespace FoundationSquareResolvers;

StabilityComponent::StabilityComponent()
{
    auto foundationResolver = new FoundationResolver;
    auto wallResolver = new WallResolver;

    foundationResolver->SetSuccessor(wallResolver);

    m_ObjectResolver = foundationResolver;
}

void StabilityComponent::CalculateStability()
{
    m_Stability = 1.0;
}