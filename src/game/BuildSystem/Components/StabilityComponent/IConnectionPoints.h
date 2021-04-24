#ifndef _BUILDINGOBJECTS_ICONNECTIONPOINTS_
#define _BUILDINGOBJECTS_ICONNECTIONPOINTS_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/Geometry.h>
#include <Utility/AimTestResult.h>
#include "ConnectionTypes.h"

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
    virtual AimTestResult GetConnectionPoint(
        p_GameObject_t object, 
        p_GameObject_t bindable, 
        int zoneId) = 0;

    /**
     * returns zoneId if success, -1 otherwise
     * */
    virtual int GetZoneIdByPosition(
        p_GameObject_t object, 
        p_GameObject_t bindable, 
        vec3 pos) = 0;

    virtual ConnectionTypes GetTypeByZone(int zoneId) = 0;

protected:
    AimTestResult CallNext(
        p_GameObject_t object, 
        p_GameObject_t bindable, 
        int zoneId);

    int CallNext(
        p_GameObject_t object, 
        p_GameObject_t bindable, 
        vec3 pos);

private:
    IConnectionPoints *m_Successor = nullptr;
};

#endif // !_BUILDINGOBJECTS_ICONNECTIONPOINTS_
