#ifndef _BUILDINGOBJECTS_IOBJECTRESOLVER_
#define _BUILDINGOBJECTS_IOBJECTRESOLVER_

#include <pch.h>

#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>
#include <Utility/AimTestResult.h>

#include "ConnectionTypes.h"
#include "../VisualizerComponent.h"

using namespace std;

class IConnectionPoints;

class IObjectResolver
{
public:
    virtual ~IObjectResolver();

    void SetSuccessor(IObjectResolver *successor);

    virtual AimTestResult TryConnect(ray ray, GameObject *object, GameObject *bindable);

    virtual void AddConnection(GameObject *object, GameObject *bindable);

    virtual bool HasConnection(int zoneId);
    virtual bool HasConnection(
        GameObject *object,
        GameObject *bindable,
        vec3 pos);

    virtual void RemoveConnection(GameObject *object, GameObject *bindable);
    virtual void RemoveConnections(GameObject *object);

    vector<Connection> GetConnections();

    virtual bool CanResolve(GameObject *object, GameObject *bindable) = 0;

protected:
    virtual void GenerateZones() = 0;
    virtual vector<Triangle> GetTransformedZone(GameObject *object, int zoneId);

    AimTestResult CallNext(ray ray, GameObject *object, GameObject *bindable);

    IConnectionPoints *m_Handler = nullptr;

    vector<vector<Triangle>> m_Zones;
    map<int, p_GameObjectWeak_t> m_Connections; // [key - zoneId, value - ptr]

private:
    IObjectResolver *m_Successor = nullptr;
    VisualizerComponent *m_Visualizer = new VisualizerComponent(0.2);
};

#endif // !_BUILDINGOBJECTS_IOBJECTRESOLVER_
