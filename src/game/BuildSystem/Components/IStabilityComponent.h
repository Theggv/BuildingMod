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

	virtual void SetParent(GameObject *parent) override;

	/**
	 * object - объект, который необходимо прибиндить
	 * */
	virtual AimTestResult TryConnect(ray ray, p_GameObject_t object);

	virtual void AddConnection(p_GameObject_t object);

	set<Connection, ConnectionOrdering> GetConnections();

	// Начать полный расчет стабильности
	void StartCalculation();
	// Вызывать после окончания расчета стабильности
	void OnStabilityCalculated();

	// Формируется из отношения родитель - потомок
	virtual void CalculatePrimaryStability() = 0;
	// Формируется из вспомогательных связей
	virtual void CalculateSecondaryStability(int cycle = 0) = 0;

	double GetStability();

protected:
	IObjectResolver *m_ObjectResolver = nullptr;

	double m_PrimaryStability;
	double m_SecondaryStability;

	bool m_IsRecalcRequired = false;

	// 	We can't use GetParent() in destruct because it's already invalid,
	// 	but we can clean up connections using object id of parent
	int m_ParentId;
};

#endif // !_BUILDINGOBJECTS_COMPONENTS_ISTABILITYCOMPONENT_
