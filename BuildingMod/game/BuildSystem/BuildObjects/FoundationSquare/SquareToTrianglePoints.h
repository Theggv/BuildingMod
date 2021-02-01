#ifndef _BUILDOBJECTS_SQUARETOTRIANGLEPOINTS_
#define _BUILDOBJECTS_SQUARETOTRIANGLEPOINTS_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/IConnectionPoints.h>
#include <game/Geometry.h>

#include "SquareZoneComponent.h"

using namespace std;

class SquareToTrianglePoints : public IConnectionPoints
{
public:
    /**
     * zoneId = (zone << 4) + heightZone
     * */
    AimTestResult GetConnectionPoint(GameObject *object, GameObject *bindable, int zoneId) override;

private:
    void ConvertZoneId(int zoneId, SquareZones &zone, HeightZones &height);
};

#endif // !_BUILDOBJECTS_SQUARETOTRIANGLEPOINTS_
