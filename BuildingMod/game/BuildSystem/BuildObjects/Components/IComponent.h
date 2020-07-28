#pragma once

#include <pch.h>

class GameObject;

class IComponent
{
public:
	IComponent();
	~IComponent();

	// Unity-like Start
	virtual void Start();
	// Unity-like Update
	virtual void Update();
	// Called when parent's transform was updated
	virtual void UpdateTransform();
	// Dispose
	virtual void Dispose();

	void SetParent(GameObject* parent);
	GameObject* GetParent();

protected:
	GameObject* m_parent;
	
	class ComponentObserver: public IObserver
	{
	public:
		ComponentObserver(IComponent*);
		~ComponentObserver();

		virtual void Update() override;

	private:
		IComponent* m_IComponent;
	};

	ComponentObserver* m_ComponentObserver;
};