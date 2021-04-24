#ifndef _BUILDSYSTEM_GAMEOBJECT_
#define _BUILDSYSTEM_GAMEOBJECT_

#include <pch.h>
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

	virtual void OnStart();
	virtual void OnUpdate();

	/// <summary>
	/// Called from AddToFullPack. Entity state saved in FrameState class
	/// </summary>
	/// <param name="isPost">Is post call</param>
	/// <returns>return 1 if entity state was changed, 0 otherwise</returns>
	virtual int OnUpdateFullPack(AddToFullPackArgs args, bool isPost);

	// Called when parent's transform was updated
	virtual void OnTransformUpdate();

	virtual void OnStateUpdated();

	Transform *GetTransform();

	unsigned long GetWorldPositionFlags();

	template <class T>
	T *GetComponent();

	template <class T>
	bool AddComponent(const T component);

	BuildState GetState();
	bool TrySetState(BuildState state);

	virtual void Connect(shared_ptr<GameObject> other);

	shared_ptr<GameObject> GetSharedPtr();

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

	unique_ptr<Transform> m_Transform;
	unique_ptr<IObserver> m_TransformObserver;

	unsigned long m_WorldPosition = 0;
};

template <class T>
T *GameObject::GetComponent()
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
bool GameObject::AddComponent(const T component)
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

typedef shared_ptr<GameObject> p_GameObject_t;
typedef weak_ptr<GameObject> p_GameObjectWeak_t;

#endif // !_BUILDSYSTEM_GAMEOBJECT_