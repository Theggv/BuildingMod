#ifndef _BUILDINGOBJECTS_COMPONENTS_ISTABILITYCOMPONENT_
#define _BUILDINGOBJECTS_COMPONENTS_ISTABILITYCOMPONENT_

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
	virtual void RemoveConnection(GameObject *object);

	set<Connection, ConnectionOrdering> GetConnections();

	virtual void CalculateStability(int cycle = 0) = 0;

	double GetStability();

protected:
	void UpdateDependentObjects(int cycle = 0);

	IObjectResolver *m_ObjectResolver = nullptr;
	double m_Stability;
};

#endif // !_BUILDINGOBJECTS_COMPONENTS_ISTABILITYCOMPONENT_
