#ifndef _BUILDOBJECTS_TRIANGLETOSQUAREPOINTS_
#define _BUILDOBJECTS_TRIANGLETOSQUAREPOINTS_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/IConnectionPoints.h>
#include <game/Geometry.h>

#include "TriangleZoneComponent.h"

using namespace std;

class TriangleToSquarePoints : public IConnectionPoints
{
public:
    /**
     * zoneId = (squareZone << 4) + heightZone
     * */
    AimTestResult GetConnectionPoint(GameObject *object, GameObject *bindable, int zoneId) override;

private:
    void ConvertZoneId(int zoneId, TriangleZones &zone, HeightZones &height);
};

#endif // !_BUILDOBJECTS_TRIANGLETOSQUAREPOINTS_
