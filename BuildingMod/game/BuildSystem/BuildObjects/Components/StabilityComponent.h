#ifndef _BUILDOBJECTS_COMPONENTS_STABILITYCOMPONENT_
#define _BUILDOBJECTS_COMPONENTS_STABILITYCOMPONENT_

#include <pch.h>
#include "IComponent.h"
#include <game/BuildSystem/ObjectManager.h>

class StabilityComponent : public IComponent
{
public:
	StabilityComponent();
	~StabilityComponent();

	// Объекты, от которых зависит стабильность текущего объекта
	void AddDependentObject(p_GameObjectWeak_t *object);
	// Объекты, стабильность которые зависят от текущего объекта
	void AddStabilityObject(p_GameObjectWeak_t *object);

	void CalculateStability();

private:
	double _stability;
};

#endif // !_BUILDOBJECTS_COMPONENTS_STABILITYCOMPONENT_
