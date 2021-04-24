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

	void OnStateUpdated() override;
	void OnStabilityCalculated();

	/**
     * object - объект, который необходимо прибиндить
     * */
	virtual AimTestResult TryConnect(ray ray, p_GameObject_t object);

	virtual void AddConnection(p_GameObject_t object);
	virtual void RemoveConnection(p_GameObject_t object);

	set<Connection, ConnectionOrdering> GetConnections();

	virtual void CalculateStability(int cycle = 0) = 0;
	void UpdateDependentObjects(int cycle = 0);

	double GetStability();

protected:
	IObjectResolver *m_ObjectResolver = nullptr;
	double m_Stability;
};

#endif // !_BUILDINGOBJECTS_COMPONENTS_ISTABILITYCOMPONENT_
