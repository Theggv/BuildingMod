#ifndef _BUILDINGOBJECTS_COMPONENTS_TRIANGLECOLLIDER_
#define _BUILDINGOBJECTS_COMPONENTS_TRIANGLECOLLIDER_

#include <pch.h>
#include <game/BuildSystem/Components/IColliderComponent.h>

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

#endif // !_BUILDINGOBJECTS_COMPONENTS_TRIANGLECOLLIDER_
