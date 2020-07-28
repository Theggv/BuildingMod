#pragma once

#include <pch.h>

using namespace std;

class ObservableVector;

class Transform: public IObservable
{
public:
	Transform();
	~Transform();

	virtual void Attach(IObserver* observer);
	virtual void Detach(IObserver* observer);
	virtual void Notify();

	ObservableVector* Position;
	// Uses only y axis
	ObservableVector* Rotation;

private:
	class TransformObserver : public IObserver
	{
	public:
		TransformObserver(Transform*);
		~TransformObserver();

		void Update() override;
	private:
		Transform* m_Transform;
	};

	TransformObserver* m_Observer;
	list<IObserver*> m_ListObservers;
};

typedef Transform transform_t;