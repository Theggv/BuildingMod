#ifndef _UTILITY_TRANSFORM_
#define _UTILITY_TRANSFORM_

#include <pch.h>

#include "IObservable.h"
#include "IObserver.h"
#include "ObservableVector.h"

using namespace std;

class ObservableTransform : public IObservable
{
public:
	ObservableTransform();
	~ObservableTransform();

	virtual void Attach(IObserver *observer) override;
	virtual void Detach(IObserver *observer) override;
	virtual void Notify() override;

	ObservableVector *GetPosition();

	// Uses only y axis
	ObservableVector *GetRotation();

private:
	class TransformObserver : public IObserver
	{
	public:
		TransformObserver(ObservableTransform *transform);
		~TransformObserver();

		void Update() override;

	private:
		ObservableTransform *m_Transform;
	};

	ObservableVector *m_Position;
	ObservableVector *m_Rotation;

	IObserver *m_Observer;
	list<IObserver *> m_ListObservers;
};

#endif // !_UTILITY_TRANSFORM_
