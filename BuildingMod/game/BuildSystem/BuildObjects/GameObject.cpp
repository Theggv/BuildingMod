#include "GameObject.h"
#include <game/BuildSystem/ObjectManager.h>
#include <Server/FrameState.h>

// initial object id
static int m_IdGenerator = 1024;

GameObject::GameObject() : Id(m_IdGenerator)
{
	m_IdGenerator++;

	m_State = BuildState::STATE_NONE;
	m_Components = set<IComponent *>();
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
	if (m_State != BuildState::STATE_SOLID)
		return 0;

	vec3 pos = *GetTransform()->GetPosition();

	auto state = FrameState::Instance().GetState(isPost);
	vec3 playerPos = state->host->v.origin;

	// 125 units
	if ((playerPos - pos).LengthSquared() > 15625)
	{
		if (!isPost)
		{
			if (state->state->renderamt == 0.0f)
				state->state->number = 0;
			else
				return 0;
		}
		else
		{
			state->state->solid = SOLID_NOT;
		}

		return 1;
	}

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

	if (m_State == BuildState::STATE_SOLID)
	{
		ObjectManager::Instance().SetMapIndex(this);
	}
}

Transform *GameObject::GetTransform()
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

bool GameObject::TrySetState(BuildState state)
{
	if (state == BuildState::STATE_NONE)
		return false;

	if (state == BuildState::STATE_SOLID &&
		(m_State == BuildState::STATE_CANNOT_BUILD || m_State == BuildState::STATE_NONE))
		return false;

	if (state == m_State)
		return false;

	m_State = state;
	StateUpdated();

	return true;
}

void GameObject::UpdateWorldPosition()
{
	m_WorldPosition = ObjectManager::CalculateWorldPosition(
		m_Transform->GetPosition()->x(),
		m_Transform->GetPosition()->y());
}

GameObject::GameObjectObserver::GameObjectObserver(GameObject *object) : m_GameObject(object)
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
