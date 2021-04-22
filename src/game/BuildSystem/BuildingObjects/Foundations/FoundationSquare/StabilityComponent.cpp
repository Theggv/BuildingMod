#include "StabilityComponent.h"

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

void StabilityComponent::CalculateStability(int cycle)
{
    // prevent random loop recursion
    if (cycle >= 100)
        return;

    m_Stability = 1.0;

    UpdateDependentObjects(cycle + 1);
}