#ifndef _BUILDOBJECTS_FOUNDATIONSQUARE_WALLPOINTS_
#define _BUILDOBJECTS_FOUNDATIONSQUARE_WALLPOINTS_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/Components/StabilityComponent/IConnectionPoints.h>
#include <game/Geometry.h>

#include "../../WallFull.h"

using namespace std;

namespace WallFullResolvers
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

#endif // !_BUILDOBJECTS_FOUNDATIONSQUARE_WALLPOINTS_
