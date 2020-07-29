#pragma once

#include <pch.h>
#include <game/Utility/IObservable.h>

using namespace std;

class ObservableVector;

class Transform: public IObservable
{
public:
	Transform();
	~Transform();

	virtual void Attach(IObserver* observer) override;
	virtual void Detach(IObserver* observer) override;
	virtual void Notify() override;

	ObservableVector* GetPosition();
	
	// Uses only y axis
	ObservableVector* GetRotation();

private:
	class TransformObserver : public IObserver
	{
	public:
		TransformObserver(Transform* transform);
		~TransformObserver();

		void Update() override;
	private:
		Transform* m_Transform;
	};

	ObservableVector* m_Position;
	ObservableVector* m_Rotation;

	IObserver* m_Observer;
	list<IObserver*> m_ListObservers;
};
