#include "GameObject.h"
#include <game/BuildSystem/ObjectManager.h>

static int m_IdGenerator;

GameObject::GameObject(): Id(m_IdGenerator)
{
	m_IdGenerator++;

	m_State = BuildState::STATE_SOLID;
	m_Components = set<IComponent*>();
	m_Transform = new Transform();
	m_TransformObserver = new GameObjectObserver(this);
}

GameObject::~GameObject()
{
	for (auto component : m_Components)
		delete component;

	m_Components.clear();

	delete this->m_TransformObserver;
	delete this->m_Transform;
}

void GameObject::Start()
{
	for (auto component : m_Components)
		component->Start();
}

void GameObject::Update()
{
	for (auto component : m_Components)
		component->Update();
}

int GameObject::UpdateFullPack(bool isPost)
{
	return 0;
}

void GameObject::UpdateTransform()
{
	UpdateWorldPosition();

	for (auto component : m_Components)
		component->UpdateTransform();
}

void GameObject::StateUpdated()
{
	for (auto component : m_Components)
		component->StateUpdated();
}

Transform* GameObject::GetTransform()
{
	return m_Transform;
}

unsigned long GameObject::GetWorldPositionFlags()
{
	return m_WorldPosition;
}

BuildState GameObject::GetState()
{
	return m_State;
}

void GameObject::SetState(BuildState state)
{
	m_State = state;
	StateUpdated();
}

void GameObject::UpdateWorldPosition()
{
	m_WorldPosition = ObjectManager::CalculateWorldPosition(
		m_Transform->GetPosition()->x(),
		m_Transform->GetPosition()->y()
	);
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
