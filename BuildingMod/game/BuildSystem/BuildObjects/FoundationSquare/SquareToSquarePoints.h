#ifndef _BUILDOBJECTS_SQUARETOSQUAREPOINTS_
#define _BUILDOBJECTS_SQUARETOSQUAREPOINTS_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/IConnectionPoints.h>
#include <game/Geometry.h>

#include "SquareZoneComponent.h"

using namespace std;

class SquareToSquarePoints : public IConnectionPoints
{
public:
    /**
     * zoneId = (squareZone << 4) + heightZone
     * */
    AimTestResult GetConnectionPoint(GameObject *object, GameObject *bindable, int zoneId) override;

private:
    void ConvertZoneId(int zoneId, SquareZones &zone, HeightZones &height);
};

#endif // !_BUILDOBJECTS_SQUARETOSQUAREPOINTS_
