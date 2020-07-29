#include "Transform.h"

Transform::Transform()
{
	m_Observer = new TransformObserver(this);

	m_Position = new ObservableVector;
	m_Rotation = new ObservableVector;

	m_Position->Attach(m_Observer);
	m_Rotation->Attach(m_Observer);
}

Transform::~Transform()
{
	m_Position->Detach(m_Observer);
	m_Rotation->Detach(m_Observer);

	delete m_Observer;

	delete m_Position;
	delete m_Rotation;
}

void Transform::Attach(IObserver* observer)
{
	m_ListObservers.push_back(observer);
}

void Transform::Detach(IObserver* observer)
{
	m_ListObservers.remove(observer);
}

void Transform::Notify()
{
	auto it = m_ListObservers.begin();

	while (it != m_ListObservers.end())
	{
		(*it)->Update();
		++it;
	}
}

Transform::TransformObserver::TransformObserver(Transform* transform)
{
	m_Transform = transform;
}

Transform::TransformObserver::~TransformObserver()
{
	
}

void Transform::TransformObserver::Update()
{
	m_Transform->Notify();
}
