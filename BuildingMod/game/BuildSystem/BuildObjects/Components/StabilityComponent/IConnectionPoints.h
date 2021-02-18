#ifndef _BUILDOBJECTS_ICONNECTIONPOINTS_
#define _BUILDOBJECTS_ICONNECTIONPOINTS_

#include <pch.h>
#include <game/Geometry.h>
#include <game/BuildSystem/BuildObjects/AimTestResult.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>

using namespace std;

class IConnectionPoints
{
public:
    virtual ~IConnectionPoints();

    void SetSuccessor(IConnectionPoints *successor);

    /**
     * object - объект, чьи зоны нужно получить
     * bindable - объект, который биндится
     * */
    virtual AimTestResult GetConnectionPoint(GameObject *object, GameObject *bindable, int zoneId) = 0;

    /**
     * returns zoneId if success, -1 otherwise
     * */
    virtual int GetZoneIdByPosition(GameObject* object, GameObject* bindable, vec3 pos) = 0;

protected:
    AimTestResult CallNext(GameObject *object, GameObject *bindable, int zoneId);
    int CallNext(GameObject *object, GameObject *bindable, vec3 pos);

private:
    IConnectionPoints *m_Successor = nullptr;
};

#endif // !_BUILDOBJECTS_ICONNECTIONPOINTS_
