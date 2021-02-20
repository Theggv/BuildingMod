#ifndef _BUILDOBJECTS_FOUNDATIONTRIANGLE_WALLRESOLVER_
#define _BUILDOBJECTS_FOUNDATIONTRIANGLE_WALLRESOLVER_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/Components/StabilityComponent/IObjectResolver.h>
#include <game/BuildSystem/BuildObjects/FoundationBase/FoundationBase.h>
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

#endif // !_BUILDOBJECTS_FOUNDATIONTRIANGLE_WALLRESOLVER_
