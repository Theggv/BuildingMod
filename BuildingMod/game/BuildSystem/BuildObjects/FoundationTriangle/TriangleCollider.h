#ifndef _BUILDOBJECTS_COMPONENTS_TRIANGLECOLLIDER_
#define _BUILDOBJECTS_COMPONENTS_TRIANGLECOLLIDER_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/Components/IColliderComponent.h>

using namespace std;

class IColliderComponent;

class TriangleCollider : public IColliderComponent
{
public:
	TriangleCollider();

	void AddEdict(edict_t *edict, bool isVisible);
	set<edict_t *> GetEdicts(bool isVisible);

	virtual void UpdateTransform() override;
};

#endif // !_BUILDOBJECTS_COMPONENTS_TRIANGLECOLLIDER_
