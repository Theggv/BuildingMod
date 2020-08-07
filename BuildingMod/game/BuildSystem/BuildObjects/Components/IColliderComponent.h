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

	void AddEdict(edict_t* edict, bool isVisible);
	set<edict_t*> GetEdicts(bool isVisible);

	virtual void UpdateTransform() override;
private:
	set<edict_t*> m_VisibleEdicts;
	set<edict_t*> m_InvisibleEdicts;
};

#endif // !_BUILDOBJECTS_COMPONENTS_ICOLLIDERCOMPONENT_
