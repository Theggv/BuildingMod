#ifndef _BUILDSYSTEM_GAMEOBJECT_
#define _BUILDSYSTEM_GAMEOBJECT_

#include <pch.h>
#include <game/BuildSystem/Components/IComponent.h>
#include <game/Server/FrameState.h>

#include <Utility/Transform.h>
#include <Utility/BuildState.h>

#include <game/Geometry.h>

using namespace std;

class IComponent;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	/// <summary>
	/// Unique id of object
	/// </summary>
	const int Id;

	// Unity-like Start
	virtual void Start();
	// Unity-like Update
	virtual void Update();

	/// <summary>
	/// Called from AddToFullPack. Entity state saved in FrameState class
	/// </summary>
	/// <param name="isPost">Is post call</param>
	/// <returns>return 1 if entity state was changed, 0 otherwise</returns>
	virtual int UpdateFullPack(AddToFullPackArgs args, bool isPost);
	// Called when parent's transform was updated
	virtual void UpdateTransform();

	virtual void StateUpdated();

	/// <summary>
	/// Get transform of the object
	/// </summary>
	/// <returns></returns>
	Transform *GetTransform();

	unsigned long GetWorldPositionFlags();

	/// <summary>
	/// Get Component by type
	/// </summary>
	/// <typeparam name="T">IComponent without pointer</typeparam>
	/// <returns>Returns IComponent if component exists, nullptr otherwise</returns>
	template <class T>
	T *GetComponent();

	/// <summary>
	/// Add new component to the object
	/// </summary>
	/// <typeparam name="T">IComponent</typeparam>
	/// <param name="component"></param>
	/// <returns>Returns true if added successfully</returns>
	template <class T>
	bool AddComponent(const T component);

	BuildState GetState();
	bool TrySetState(BuildState state);

	virtual void Connect(GameObject *other) = 0;

protected:
	set<IComponent *> m_Components;
	BuildState m_State;

	void UpdateWorldPosition();

private:
	class GameObjectObserver : public IObserver
	{
	public:
		GameObjectObserver(GameObject *object);
		~GameObjectObserver();

		virtual void Update() override;

	private:
		GameObject *m_GameObject;
	};

	Transform *m_Transform;
	IObserver *m_TransformObserver;

	unsigned long m_WorldPosition = 0;
};

template <class T>
inline T *GameObject::GetComponent()
{
	// assert that T is IComponent
	static_assert(is_base_of<IComponent, T>::value, "Type parameter must derive from IComponent");

	for (auto component : m_Components)
	{
		if (auto casted = dynamic_cast<T *>(component))
			return casted;
	}

	return nullptr;
}

template <class T>
inline bool GameObject::AddComponent(const T component)
{
	// assert that T is IComponent
	using type = remove_pointer_t<T>;
	static_assert(is_base_of<IComponent, type>::value, "Type parameter must derive from IComponent");

	if (GetComponent<type>())
		return false;

	component->SetParent(this);

	m_Components.insert(component);

	return true;
}

#endif // !_BUILDSYSTEM_GAMEOBJECT_