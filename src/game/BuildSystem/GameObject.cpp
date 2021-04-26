#include "GameObject.h"
#include <game/BuildSystem/ObjectManager.h>
#include <Server/FrameState.h>

#include <game/BuildSystem/Components/IComponent.h>
#include <game/BuildSystem/Components/IStabilityComponent.h>

// initial object id
static int m_IdGenerator = 1024;

GameObject::GameObject() : Id(m_IdGenerator)
{
	m_IdGenerator++;

	m_State = BuildState::STATE_NONE;
	m_Components = set<IComponent *>();
	m_Transform = make_unique<Transform>();
	m_TransformObserver = make_unique<GameObjectObserver>(this);

	ObjectManager::Instance().Add(shared_ptr<GameObject>(this));
	m_WeakPtr = ObjectManager::Instance().GetPtr(Id);
}

GameObject::~GameObject()
{
	for (auto component : m_Components)
	{
		component->SetValid(false);
		delete component;
	}

	m_Components.clear();

	// Trick to clear memory allocated by STL container
	set<IComponent *>().swap(m_Components);

	if (this->m_TransformObserver)
		this->m_TransformObserver.reset();

	if (this->m_Transform != nullptr)
		this->m_Transform.reset();
}

void GameObject::OnStart()
{
	for (auto component : m_Components)
		component->OnStart();

	UpdateWorldPosition();
}

void GameObject::OnUpdate()
{
	for (auto component : m_Components)
		component->OnUpdate();
}

int GameObject::OnUpdateFullPack(AddToFullPackArgs args, bool isPost)
{
	if (m_State != BuildState::STATE_SOLID)
		return 0;

	vec3 pos = *GetTransform()->GetPosition();

	vec3 playerPos = args.host->v.origin;

	// 125 units
	if ((playerPos - pos).LengthSquared() > 15625)
	{
		if (!isPost)
		{
			if (args.state->rendermode != kRenderNormal &&
				args.state->renderamt == 0.0f)
				args.state->number = -1;
			else
				return 0;
		}
		else
			args.state->solid = SOLID_NOT;

		return MRES_SUPERCEDE;
	}

	return 0;
}

void GameObject::OnTransformUpdate()
{
	UpdateWorldPosition();

	for (auto component : m_Components)
		component->OnTransformUpdate();
}

void GameObject::OnStateUpdated()
{
	for (auto component : m_Components)
		component->OnStateUpdated();

	if (m_State == BuildState::STATE_SOLID)
	{
		ObjectManager::Instance().SetMapIndex(ObjectManager::Instance().Get(Id));
	}
}

Transform *GameObject::GetTransform()
{
	return m_Transform.get();
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
	OnStateUpdated();

	return true;
}

void GameObject::UpdateWorldPosition()
{
	m_WorldPosition = ObjectManager::CalculateWorldPosition(
		m_Transform->GetPosition()->x(),
		m_Transform->GetPosition()->y());
}

GameObject::GameObjectObserver::GameObjectObserver(GameObject *object)
	: m_GameObject(object)
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
	m_GameObject->OnTransformUpdate();
}

void GameObject::Connect(p_GameObject_t other)
{
	auto thisStability = this->GetComponent<IStabilityComponent>();
	auto otherStability = other->GetComponent<IStabilityComponent>();

	if (thisStability != nullptr)
		thisStability->AddConnection(other);

	if (otherStability != nullptr)
		otherStability->AddConnection(this->GetSharedPtr());
}

shared_ptr<GameObject> GameObject::GetSharedPtr()
{
	return m_WeakPtr.lock();
}
