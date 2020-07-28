#include "Transform.h"

Transform::Transform(): Rotation(), Position()
{
	m_Observer = new TransformObserver(this);

	Position.Attach(m_Observer);
	Rotation.Attach(m_Observer);
}

Transform::~Transform()
{
	Position.Detach(m_Observer);
	Rotation.Detach(m_Observer);

	delete m_Observer;
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

	while (it !+ m_ListObservers.end())
	{
		(*it)->Update();
		++it;
	}
}

Transform::TransformObserver::TransformObserver(Transform* transform) : m_Transform(transform) {}

Transform::TransformObserver::~TransformObserver() {}

void Transform::TransformObserver::Update()
{
	m_Transform->Notify();
}
