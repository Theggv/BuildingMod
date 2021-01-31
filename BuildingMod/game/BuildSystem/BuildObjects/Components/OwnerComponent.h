#ifndef _BUILDOBJECTS_COMPONENTS_OWNERCOMPONENT_
#define _BUILDOBJECTS_COMPONENTS_OWNERCOMPONENT_

#include <pch.h>
#include "IComponent.h"

class OwnerComponent : public IComponent
{
public:
	OwnerComponent(edict_t *owner);
	~OwnerComponent();

	virtual void Update() override;
	virtual void StateUpdated() override;

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
	edict_t *m_Owner;
};

#endif // !_BUILDOBJECTS_COMPONENTS_OWNERCOMPONENT_
