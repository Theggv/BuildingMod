#ifndef _BUILDOBJECTS_COMPONENTS_ISTABILITYCOMPONENT_
#define _BUILDOBJECTS_COMPONENTS_ISTABILITYCOMPONENT_

#include <pch.h>
#include "IComponent.h"

#include <game/Geometry.h>
#include <game/BuildSystem/ObjectManager.h>
#include "StabilityComponent/IConnectionPoints.h"
#include "StabilityComponent/IObjectResolver.h"

using namespace std;

class IComponent;

/**
 * Component that stores precalculated trigger zones
 * */
class IStabilityComponent : public IComponent
{
public:
    IStabilityComponent();
    virtual ~IStabilityComponent();

    /**
     * object - объект, который необходимо прибиндить
     * */
    virtual AimTestResult TryConnect(ray ray, GameObject *object);

    virtual void AddConnection(GameObject *object);
    virtual bool HasConnection(GameObject *object, vec3 pos);
    virtual void RemoveConnection(GameObject *object);

    vector<p_GameObjectWeak_t> GetConnections();

    virtual void CalculateStability() = 0;

    double GetStability();

protected:
    IObjectResolver *m_ObjectResolver = nullptr;
    double m_Stability;
};

#endif // !_BUILDOBJECTS_COMPONENTS_ISTABILITYCOMPONENT_
