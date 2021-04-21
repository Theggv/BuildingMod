#ifndef _BUILDINGOBJECTS_COMPONENTS_ICOMPONENT_
#define _BUILDINGOBJECTS_COMPONENTS_ICOMPONENT_

#include <game/BuildSystem/GameObject.h>

class GameObject;

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
	void SetParent(GameObject *parent);
	GameObject *GetParent();

protected:
	GameObject *m_Parent = nullptr;
};

#endif // !_BUILDINGOBJECTS_COMPONENTS_ICOMPONENT_