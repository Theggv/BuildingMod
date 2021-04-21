#ifndef _BUILDINGOBJECTS_FOUNDATIONSQUARE_STABILITYCOMPONENT_
#define _BUILDINGOBJECTS_FOUNDATIONSQUARE_STABILITYCOMPONENT_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/IStabilityComponent.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

#include <game/BuildSystem/BuildingObjects/Objects.h>

using namespace std;

namespace FoundationSquareResolvers
{
    class StabilityComponent : public IStabilityComponent
    {
    public:
        StabilityComponent();

        virtual void CalculateStability() override;
    };
}

#endif // !_BUILDINGOBJECTS_FOUNDATIONSQUARE_STABILITYCOMPONENT_
