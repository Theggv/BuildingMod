#ifndef _BUILDINGOBJECTS_FOUNDATIONTRIANGLE_WALLPOINTS_
#define _BUILDINGOBJECTS_FOUNDATIONTRIANGLE_WALLPOINTS_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/StabilityComponent/IConnectionPoints.h>
#include <game/Geometry.h>

#include "../../FoundationTriangle.h"

using namespace std;

namespace FoundationTriangleResolvers
{
    class WallPoints : public IConnectionPoints
    {
    public:
        /**
     * zoneId = (squareZone << 4) + heightZone
     * */
        AimTestResult GetConnectionPoint(GameObject *object, GameObject *bindable, int zoneId) override;

        virtual int GetZoneIdByPosition(GameObject *object, GameObject *bindable, vec3 pos) override;
    };
}

#endif // !_BUILDINGOBJECTS_FOUNDATIONTRIANGLE_WALLPOINTS_
