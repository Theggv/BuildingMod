#ifndef _BUILDOBJECTS_WALLFULL_STABILITYCOMPONENT_
#define _BUILDOBJECTS_WALLFULL_STABILITYCOMPONENT_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/Components/IStabilityComponent.h>
#include <game/BuildSystem/BuildObjects/FoundationBase/FoundationBase.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

#include "WallFull.h"

using namespace std;

namespace WallFullResolvers
{
    class StabilityComponent : public IStabilityComponent
    {
    public:
        StabilityComponent();

        virtual void CalculateStability() override;
    };
}

#endif // !_BUILDOBJECTS_WALLFULL_STABILITYCOMPONENT_
