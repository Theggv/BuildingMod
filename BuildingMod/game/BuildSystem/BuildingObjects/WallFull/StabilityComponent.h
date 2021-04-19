#ifndef _BUILDINGOBJECTS_WALLFULL_STABILITYCOMPONENT_
#define _BUILDINGOBJECTS_WALLFULL_STABILITYCOMPONENT_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/IStabilityComponent.h>
#include <game/BuildSystem/BuildingObjects/FoundationBase/FoundationBase.h>
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

#endif // !_BUILDINGOBJECTS_WALLFULL_STABILITYCOMPONENT_
