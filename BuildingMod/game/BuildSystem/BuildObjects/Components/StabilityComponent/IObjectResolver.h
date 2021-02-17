#ifndef _BUILDOBJECTS_IOBJECTRESOLVER_
#define _BUILDOBJECTS_IOBJECTRESOLVER_

#include <pch.h>

#include <game/Geometry.h>
#include <game/BuildSystem/BuildObjects/AimTestResult.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>

using namespace std;

class IConnectionPoints;

class IObjectResolver
{
public:
    virtual ~IObjectResolver();

    void SetSuccessor(IObjectResolver *successor);

    virtual AimTestResult TryConnect(ray ray, GameObject *object, GameObject *bindable);

    virtual void AddConnection(GameObject *object, GameObject *bindable);
    virtual bool HasConnection(GameObject *object, GameObject *bindable, vec3 pos);

    virtual bool CanResolve(GameObject *object, GameObject *bindable) = 0;

protected:
    virtual void GenerateZones() = 0;
    virtual vector<Triangle> GetTransformedZone(GameObject *object, int zoneId);

    AimTestResult CallNext(ray ray, GameObject *object, GameObject *bindable);

    IConnectionPoints *m_Handler;

    vector<vector<Triangle>> m_Zones;
    map<int, GameObject *> m_Connections;

private:
    IObjectResolver *m_Successor;
};

#endif // !_BUILDOBJECTS_IOBJECTRESOLVER_
