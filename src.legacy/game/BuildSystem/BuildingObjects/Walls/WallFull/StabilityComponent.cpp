#include "StabilityComponent.h"

// Object resolvers
#include "../Resolvers/AdditionalResolver.h"
#include "Resolvers/Wall/WallResolver.h"

using namespace WallBaseResolvers;
using namespace WallFullResolvers;

StabilityComponent::StabilityComponent()
{
    auto additionalResolver = new AdditionalResolver;
    auto wallResolver = new WallResolver;

    additionalResolver->SetSuccessor(wallResolver);

    m_ObjectResolver = additionalResolver;
}