#ifndef _BUILDOBJECTS_TRIANGLETOTRIANGLEPOINTS_
#define _BUILDOBJECTS_TRIANGLETOTRIANGLEPOINTS_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/IConnectionPoints.h>
#include <game/Geometry.h>

#include "TriangleZoneComponent.h"

using namespace std;

class TriangleToTrianglePoints : public IConnectionPoints
{
public:
    /**
     * zoneId = (zone << 4) + heightZone
     * */
    AimTestResult GetConnectionPoint(GameObject *object, GameObject *bindable,int zoneId) override;

private:
    void ConvertZoneId(int zoneId, TriangleZones &zone, HeightZones &height);
};

#endif // !_BUILDOBJECTS_TRIANGLETOTRIANGLEPOINTS_
