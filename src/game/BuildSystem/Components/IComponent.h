#ifndef _BUILDINGOBJECTS_COMPONENTS_ICOMPONENT_
#define _BUILDINGOBJECTS_COMPONENTS_ICOMPONENT_

#include <game/BuildSystem/GameObject.h>

class IComponent
{
public:
	IComponent();
	virtual ~IComponent();

	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnTransformUpdate();
	virtual void OnStateUpdated();

	/// <summary>
	/// Set parent of component.
	/// </summary>
	/// <param name="parent"></param>
	virtual void SetParent(GameObject *parent);
	p_GameObject_t GetParent();

	void SetValid(bool isValid);

protected:
	p_GameObjectWeak_t m_Parent;
	bool m_IsValid = true;
};

#endif // !_BUILDINGOBJECTS_COMPONENTS_ICOMPONENT_