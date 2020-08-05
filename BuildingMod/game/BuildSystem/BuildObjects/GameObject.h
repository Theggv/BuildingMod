#pragma once

#include <pch.h>
#include <BuildSystem/BuildObjects/Transform.h>
#include <BuildSystem/BuildObjects/Components/IComponent.h>

using namespace std;

class IComponent;
class Transform;

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
	// Called from AddToFullPack
	virtual void UpdateFullPack(bool isPost);
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
	class GameObjectObserver : public IObserver
	{
	public:
		GameObjectObserver(GameObject* object);
		~GameObjectObserver();

		virtual void Update() override;

	private:
		GameObject* m_GameObject;
	};

	Transform* m_Transform;
	IObserver* m_TransformObserver;
};