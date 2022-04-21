#ifndef _BUILDINGOBJECTS_SQUARETOSQUAREPOINTS_
#define _BUILDINGOBJECTS_SQUARETOSQUAREPOINTS_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/StabilityComponent/IConnectionPoints.h>
#include <game/Geometry.h>

#include "../../FoundationSquare.h"

using namespace std;

class SquareToSquarePoints : public IConnectionPoints
{
public:
    /**
     * zoneId = (squareZone << 4) + heightZone
     * */
    AimTestResult GetConnectionPoint(GameObject *object, GameObject *bindable, int zoneId) override;

    virtual int GetZoneIdByPosition(GameObject *object, GameObject *bindable, vec3 pos) override;

    virtual ConnectionTypes GetTypeByZone(int zoneId) override;

private:
    void ConvertZoneId(int zoneId, SquareZones &zone, HeightZones &height);
};

#endif // !_BUILDINGOBJECTS_SQUARETOSQUAREPOINTS_
