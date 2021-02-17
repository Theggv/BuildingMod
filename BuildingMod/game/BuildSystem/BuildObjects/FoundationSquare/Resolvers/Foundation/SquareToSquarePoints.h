#ifndef _BUILDOBJECTS_SQUARETOSQUAREPOINTS_
#define _BUILDOBJECTS_SQUARETOSQUAREPOINTS_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/Components/StabilityComponent/IConnectionPoints.h>
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

    virtual int GetZoneIdByPosition(GameObject* object, GameObject* bindable, vec3 pos) override;

private:
    void ConvertZoneId(int zoneId, SquareZones &zone, HeightZones &height);
};

#endif // !_BUILDOBJECTS_SQUARETOSQUAREPOINTS_
