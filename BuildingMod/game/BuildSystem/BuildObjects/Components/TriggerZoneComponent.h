#ifndef _BUILDOBJECTS_COMPONENTS_TRIGGERZONECOMPONENT_
#define _BUILDOBJECTS_COMPONENTS_TRIGGERZONECOMPONENT_

#include <pch.h>
#include "IComponent.h"

#include <game/Geometry.h>
#include <game/BuildSystem/BuildObjects/IConnectionPoints.h>

using namespace std;

class IComponent;

/**
 * Component that stores precalculated trigger zones
 * */
class TriggerZoneComponent : public IComponent
{
public:
    TriggerZoneComponent();
    ~TriggerZoneComponent();

    /**
     * object - объект, который необходимо прибиндить
     * */
    virtual AimTestResult TryConnect(ray ray, GameObject *object);

    virtual void AddConnection(GameObject *object) = 0;

protected:
    IConnectionPoints *m_Handler;
    vector<vector<Triangle>> m_Zones;

    virtual void GenerateZones() = 0;
    virtual vector<Triangle> GetTransformedZone(GameObject *object, int zoneId) = 0;
};

#endif // !_BUILDOBJECTS_COMPONENTS_TRIGGERZONECOMPONENT_
