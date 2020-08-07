#ifndef _BUILDOBJECTS_COMPONENTS_OWNERCOMPONENT_
#define _BUILDOBJECTS_COMPONENTS_OWNERCOMPONENT_

#include <pch.h>
#include "IComponent.h"

class OwnerComponent : public IComponent
{
public:
	OwnerComponent(edict_t* owner);
	~OwnerComponent();

	/// <summary>
	/// Get current owner
	/// </summary>
	/// <returns></returns>
	edict_t* GetOwner();

	/// <summary>
	/// Set new owner
	/// </summary>
	/// <param name="owner"></param>
	void SetOwner(edict_t* owner);
private:
	edict_t* m_Owner;
};

#endif // !_BUILDOBJECTS_COMPONENTS_OWNERCOMPONENT_
