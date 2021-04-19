#ifndef _BUILDINGOBJECTS_SQUARETOTRIANGLEPOINTS_
#define _BUILDINGOBJECTS_SQUARETOTRIANGLEPOINTS_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/StabilityComponent/IConnectionPoints.h>
#include <game/Geometry.h>

#include "../../FoundationSquare.h"

using namespace std;

class SquareToTrianglePoints : public IConnectionPoints
{
public:
    /**
     * zoneId = (zone << 4) + heightZone
     * */
    AimTestResult GetConnectionPoint(GameObject *object, GameObject *bindable, int zoneId) override;

    virtual int GetZoneIdByPosition(GameObject *object, GameObject *bindable, vec3 pos) override;

private:
    void ConvertZoneId(int zoneId, SquareZones &zone, HeightZones &height);
};

#endif // !_BUILDINGOBJECTS_SQUARETOTRIANGLEPOINTS_
