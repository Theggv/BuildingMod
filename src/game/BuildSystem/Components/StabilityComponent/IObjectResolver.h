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

    virtual AimTestResult TryConnect(ray ray, p_GameObject_t object, p_GameObject_t bindable);

    virtual void AddConnection(p_GameObject_t object, p_GameObject_t bindable);

    virtual bool HasConnection(int zoneId);

    virtual void RemoveConnection(p_GameObject_t object, p_GameObject_t bindable);
    virtual void RemoveConnections(p_GameObject_t object);

    virtual bool CanResolve(p_GameObject_t object, p_GameObject_t bindable) = 0;

protected:
    virtual void GenerateZones() = 0;
    virtual vector<Triangle> GetTransformedZone(p_GameObject_t object, int zoneId);

    AimTestResult CallNext(ray ray, p_GameObject_t object, p_GameObject_t bindable);

    IConnectionPoints *m_Handler = nullptr;

    vector<vector<Triangle>> m_Zones;
    map<int, p_GameObjectWeak_t> m_Connections; // [key - zoneId, value - ptr]

protected:
    IObjectResolver *m_Successor = nullptr;
    VisualizerComponent *m_Visualizer = new VisualizerComponent(0.2);
};

#endif // !_BUILDINGOBJECTS_IOBJECTRESOLVER_
