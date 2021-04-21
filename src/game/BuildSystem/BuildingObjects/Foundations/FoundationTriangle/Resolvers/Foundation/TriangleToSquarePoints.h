#ifndef _BUILDINGOBJECTS_TRIANGLETOSQUAREPOINTS_
#define _BUILDINGOBJECTS_TRIANGLETOSQUAREPOINTS_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/StabilityComponent/IConnectionPoints.h>
#include <game/Geometry.h>

#include "../../FoundationTriangle.h"

using namespace std;

class TriangleToSquarePoints : public IConnectionPoints
{
public:
    /**
     * zoneId = (squareZone << 4) + heightZone
     * */
    AimTestResult GetConnectionPoint(GameObject *object, GameObject *bindable, int zoneId) override;

    virtual int GetZoneIdByPosition(GameObject *object, GameObject *bindable, vec3 pos) override;

    virtual ConnectionTypes GetTypeByZone(int zoneId) override;

private:
    void ConvertZoneId(int zoneId, TriangleZones &zone, HeightZones &height);
};

#endif // !_BUILDINGOBJECTS_TRIANGLETOSQUAREPOINTS_
