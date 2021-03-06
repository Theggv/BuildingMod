#ifndef _BUILDINGOBJECTS_COMPONENTS_ICOLLIDERCOMPONENT_
#define _BUILDINGOBJECTS_COMPONENTS_ICOLLIDERCOMPONENT_

#include <pch.h>
#include "IComponent.h"
#include <game/Geometry.h>

using namespace std;

class IComponent;

class IColliderComponent : public IComponent
{
public:
	IColliderComponent();
	~IColliderComponent();

	/**
	 * note: Should be call after gameobject.AddComponent()!
	 * */
	virtual void AddEdict(edict_t *edict, bool isVisible);
	virtual set<edict_t *> GetEdicts(bool isVisible);

	virtual void OnTransformUpdate() override;
	virtual void OnStateUpdated() override;

protected:
	set<edict_t *> m_VisibleEdicts;
	set<edict_t *> m_InvisibleEdicts;

	Shape *m_Shape = nullptr;
};

#endif // !_BUILDINGOBJECTS_COMPONENTS_ICOLLIDERCOMPONENT_
