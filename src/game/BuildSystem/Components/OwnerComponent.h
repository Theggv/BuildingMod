#ifndef _BUILDINGOBJECTS_COMPONENTS_OWNERCOMPONENT_
#define _BUILDINGOBJECTS_COMPONENTS_OWNERCOMPONENT_

#include <pch.h>
#include "IComponent.h"

class OwnerComponent : public IComponent
{
public:
	OwnerComponent(edict_t *owner);
	~OwnerComponent();

	virtual void OnUpdate() override;
	virtual void OnStateUpdated() override;

	/// <summary>
	/// Get current owner
	/// </summary>
	/// <returns></returns>
	edict_t *GetOwner();

	/// <summary>
	/// Set new owner
	/// </summary>
	/// <param name="owner"></param>
	void SetOwner(edict_t *owner);

	vec3 GetViewAngles();
	vec3 GetAimDest(double maxTriggerDistance = 10000.0f);
	ray GetAimRay(vec3 destination, double maxRayLength);

private:
	edict_t *m_Owner = nullptr;
};

#endif // !_BUILDINGOBJECTS_COMPONENTS_OWNERCOMPONENT_
