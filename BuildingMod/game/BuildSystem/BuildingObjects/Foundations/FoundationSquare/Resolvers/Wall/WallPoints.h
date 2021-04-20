#ifndef _BUILDINGOBJECTS_FOUNDATIONSQUARE_WALLPOINTS_
#define _BUILDINGOBJECTS_FOUNDATIONSQUARE_WALLPOINTS_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/StabilityComponent/IConnectionPoints.h>
#include <game/Geometry.h>

#include "../../FoundationSquare.h"

using namespace std;

namespace FoundationSquareResolvers
{
    class WallPoints : public IConnectionPoints
    {
    public:
        /**
     * zoneId = (squareZone << 4) + heightZone
     * */
        AimTestResult GetConnectionPoint(GameObject *object, GameObject *bindable, int zoneId) override;

        virtual int GetZoneIdByPosition(GameObject *object, GameObject *bindable, vec3 pos) override;

        virtual ConnectionTypes GetTypeByZone(int zoneId) override;
    };
}

#endif // !_BUILDINGOBJECTS_FOUNDATIONSQUARE_WALLPOINTS_
