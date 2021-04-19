#ifndef _BUILDINGOBJECTS_FOUNDATIONTRIANGLE_WALLRESOLVER_
#define _BUILDINGOBJECTS_FOUNDATIONTRIANGLE_WALLRESOLVER_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/StabilityComponent/IObjectResolver.h>
#include <game/BuildSystem/BuildingObjects/FoundationBase/FoundationBase.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

#include "../../FoundationTriangle.h"

using namespace std;

namespace FoundationTriangleResolvers
{
    class WallResolver : public IObjectResolver
    {
    public:
        WallResolver();

        virtual bool CanResolve(GameObject *object, GameObject *bindable) override;
        vector<Triangle> GetTransformedZone(GameObject *object, int zoneId) override;

    protected:
        void GenerateZones() override;

        vector<Triangle> GenerateZone(int zoneId);
    };
}

#endif // !_BUILDINGOBJECTS_FOUNDATIONTRIANGLE_WALLRESOLVER_
