#ifndef _BUILDOBJECTS_COMPONENTS_ICOMPONENT_
#define _BUILDOBJECTS_COMPONENTS_ICOMPONENT_

#include <game/BuildSystem/BuildObjects/GameObject.h>

class GameObject;

class IComponent
{
public:
	IComponent();
	virtual ~IComponent();

	// Unity-like Start
	virtual void Start();
	// Unity-like Update
	virtual void Update();
	// Called when parent's transform was updated
	virtual void UpdateTransform();
	// State updated
	virtual void StateUpdated();

	/// <summary>
	/// Set parent of component.
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(GameObject *parent);
	GameObject *GetParent();

protected:
	GameObject *m_parent;
};

#endif // !_BUILDOBJECTS_COMPONENTS_ICOMPONENT_