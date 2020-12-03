#ifndef _BUILDOBJECTS_COMPONENTS_ICOLLIDERCOMPONENT_
#define _BUILDOBJECTS_COMPONENTS_ICOLLIDERCOMPONENT_

#include <pch.h>
#include "IComponent.h"

using namespace std;

class IComponent;

class IColliderComponent : public IComponent
{
public:
	IColliderComponent();
	~IColliderComponent();

	virtual void AddEdict(edict_t* edict, bool isVisible);
	virtual set<edict_t*> GetEdicts(bool isVisible);

	virtual void UpdateTransform() override;
	virtual void StateUpdated() override;
protected:
	set<edict_t*> m_VisibleEdicts;
	set<edict_t*> m_InvisibleEdicts;
};

#endif // !_BUILDOBJECTS_COMPONENTS_ICOLLIDERCOMPONENT_
