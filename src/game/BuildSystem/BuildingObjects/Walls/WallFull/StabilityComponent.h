#ifndef _BUILDINGOBJECTS_WALLFULL_STABILITYCOMPONENT_
#define _BUILDINGOBJECTS_WALLFULL_STABILITYCOMPONENT_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

#include "../StabilityComponentBase.h"
#include <game/BuildSystem/BuildingObjects/Objects.h>

using namespace std;

namespace WallFullResolvers
{
    class StabilityComponent : public WallBaseResolvers::StabilityComponentBase
    {
    public:
        StabilityComponent();
    };
}

#endif // !_BUILDINGOBJECTS_WALLFULL_STABILITYCOMPONENT_
