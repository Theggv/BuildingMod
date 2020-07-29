#pragma once

#include <pch.h>
#include "Components/IComponent.h"
#include "Components/Transform.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();

	/// <summary>
	/// Unique id of object
	/// </summary>
	const int Id;

	// Unity-like Start
	virtual void Start();
	// Unity-like Update
	virtual void Update();
	// Called when parent's transform was updated
	virtual void UpdateTransform();
	// Dispose
	virtual void Dispose();

	/// <summary>
	/// Get transform of the object
	/// </summary>
	/// <returns></returns>
	Transform* GetTransform();

protected:
	set<IComponent*> m_Components;

private:
	Transform* m_Transform;

	class GameObjectObserver : public IObserver
	{
	public:
		GameObjectObserver(GameObject* object);
		~GameObjectObserver();

		virtual void Update() override;

	private:
		GameObject* m_GameObject;
	};

	IObserver* m_TransformObserver;
};