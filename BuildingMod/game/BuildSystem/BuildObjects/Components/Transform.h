#pragma once

#include <pch.h>
#include <utility/IObservable.h>

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

	IObserver* m_Observer;
	list<IObserver*> m_ListObservers;
};
