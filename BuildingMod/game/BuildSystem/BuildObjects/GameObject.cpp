#include "GameObject.h"

static int m_IdGenerator;

GameObject::GameObject(): Id(m_IdGenerator)
{
	m_IdGenerator++;

	m_Components = set<IComponent*>();
	m_Transform = new Transform();
	m_TransformObserver = new GameObjectObserver(this);
}

GameObject::~GameObject()
{
	m_Components.clear();

	delete this->m_TransformObserver;
	delete this->m_Transform;
}

void GameObject::Start()
{
	auto it = m_Components.begin();

	while (it != m_Components.end())
	{
		(*it)->Start();
		++it;
	}
}

void GameObject::Update()
{
	auto it = m_Components.begin();

	while (it != m_Components.end())
	{
		(*it)->Update();
		++it;
	}
}

void GameObject::UpdateTransform()
{
	auto it = m_Components.begin();

	while (it != m_Components.end())
	{
		(*it)->UpdateTransform();
		++it;
	}
}

void GameObject::Dispose()
{
}

Transform* GameObject::GetTransform()
{
	return m_Transform;
}

GameObject::GameObjectObserver::GameObjectObserver(GameObject* object) : m_GameObject(object)
{
	m_GameObject->GetTransform()->Attach(this);
}

GameObject::GameObjectObserver::~GameObjectObserver()
{
	if (m_GameObject->GetTransform() != nullptr)
		m_GameObject->GetTransform()->Detach(this);
}

void GameObject::GameObjectObserver::Update()
{
	m_GameObject->UpdateTransform();
}
