#ifndef _BUILDOBJECTS_COMPONENTS_ICOLLIDERCOMPONENT_
#define _BUILDOBJECTS_COMPONENTS_ICOLLIDERCOMPONENT_

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

	virtual void UpdateTransform() override;
	virtual void StateUpdated() override;

protected:
	set<edict_t *> m_VisibleEdicts;
	set<edict_t *> m_InvisibleEdicts;

	Shape *m_Shape;
};

#endif // !_BUILDOBJECTS_COMPONENTS_ICOLLIDERCOMPONENT_
