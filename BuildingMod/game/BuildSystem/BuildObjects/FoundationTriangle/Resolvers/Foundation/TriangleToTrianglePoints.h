#ifndef _BUILDOBJECTS_TRIANGLETOTRIANGLEPOINTS_
#define _BUILDOBJECTS_TRIANGLETOTRIANGLEPOINTS_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/Components/StabilityComponent/IConnectionPoints.h>
#include <game/Geometry.h>

#include "../../FoundationTriangle.h"

using namespace std;

class TriangleToTrianglePoints : public IConnectionPoints
{
public:
    /**
     * zoneId = (zone << 4) + heightZone
     * */
    AimTestResult GetConnectionPoint(GameObject *object, GameObject *bindable, int zoneId) override;

    virtual int GetZoneIdByPosition(GameObject *object, GameObject *bindable, vec3 pos) override;

private:
    void ConvertZoneId(int zoneId, TriangleZones &zone, HeightZones &height);
};

#endif // !_BUILDOBJECTS_TRIANGLETOTRIANGLEPOINTS_
