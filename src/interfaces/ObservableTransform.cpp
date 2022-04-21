#include "ObservableTransform.h"

ObservableTransform::ObservableTransform()
{
	m_Observer = new TransformObserver(this);

	m_Position = new ObservableVector;
	m_Rotation = new ObservableVector;

	m_Position->Attach(m_Observer);
	m_Rotation->Attach(m_Observer);
}

ObservableTransform::~ObservableTransform()
{
	m_Position->Detach(m_Observer);
	m_Rotation->Detach(m_Observer);

	delete m_Observer;

	delete m_Position;
	delete m_Rotation;
}

void ObservableTransform::Attach(IObserver *observer)
{
	m_ListObservers.push_back(observer);
}

void ObservableTransform::Detach(IObserver *observer)
{
	m_ListObservers.remove(observer);
}

void ObservableTransform::Notify()
{
	auto it = m_ListObservers.begin();

	while (it != m_ListObservers.end())
	{
		(*it)->Update();
		++it;
	}
}

ObservableVector *ObservableTransform::GetPosition()
{
	return m_Position;
}

ObservableVector *ObservableTransform::GetRotation()
{
	return m_Rotation;
}

ObservableTransform::TransformObserver::TransformObserver(ObservableTransform *ObservableTransform)
{
	m_Transform = ObservableTransform;
}

ObservableTransform::TransformObserver::~TransformObserver()
{
}

void ObservableTransform::TransformObserver::Update()
{
	m_Transform->Notify();
}
