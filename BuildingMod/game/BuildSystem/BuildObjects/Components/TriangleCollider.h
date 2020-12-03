#ifndef _BUILDOBJECTS_COMPONENTS_TRIANGLECOLLIDER_
#define _BUILDOBJECTS_COMPONENTS_TRIANGLECOLLIDER_

#include <pch.h>
#include "IColliderComponent.h"

using namespace std;

class IColliderComponent;

class TriangleCollider : public IColliderComponent
{
public:
	void AddEdict(edict_t* edict, bool isVisible);
	set<edict_t*> GetEdicts(bool isVisible);

	virtual void UpdateTransform() override;
};

#endif // !_BUILDOBJECTS_COMPONENTS_TRIANGLECOLLIDER_
