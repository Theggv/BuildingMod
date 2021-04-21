#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
}

ConnectionManager::~ConnectionManager()
{
}

ConnectionManager &ConnectionManager::Instance()
{
	static ConnectionManager manager;

	return manager;
}

bool ConnectionManager::AddLinkParentChild(GameObject *parent, GameObject *child)
{
	if (GetRelationship(parent, child) != ConnectionTypes::Unknown)
		return false;

	if (m_Children.find(parent->Id) == m_Children.end())
		m_Children.insert({parent->Id, map<int, p_GameObjectWeak_t>()});

	if (m_Parents.find(child->Id) == m_Parents.end())
		m_Parents.insert({child->Id, map<int, p_GameObjectWeak_t>()});

	auto res1 = m_Children[parent->Id].insert(
		{child->Id,
		 ObjectManager::Instance().GetPtr(child->Id)});

	auto res2 = m_Parents[child->Id].insert(
		{parent->Id,
		 ObjectManager::Instance().GetPtr(parent->Id)});

	return res1.second && res2.second;
}

bool ConnectionManager::AddLinkIndependent(GameObject *object, GameObject *other)
{
	if (GetRelationship(object, other) != ConnectionTypes::Unknown)
		return false;

	auto index = Index(object->Id, other->Id);

	// Check for duplicates
	if (m_Independent.find(index) != m_Independent.end())
		return false;

	m_Independent.insert(index);

	return true;
}

bool ConnectionManager::AddLinkAdditional(GameObject *object, GameObject *other)
{
	if (GetRelationship(object, other) != ConnectionTypes::Unknown)
		return false;

	auto index = Index(object->Id, other->Id);

	// Check for duplicates
	if (m_Additionals.find(index) != m_Additionals.end())
		return false;

	m_Additionals.insert(index);

	return true;
}

vector<p_GameObjectWeak_t> ConnectionManager::GetChildren(GameObject *parent)
{
	auto list = vector<p_GameObjectWeak_t>();

	if (m_Children.find(parent->Id) != m_Children.end())
	{
		for (auto pair : m_Children[parent->Id])
			list.push_back(pair.second);
	}

	return list;
}

vector<p_GameObjectWeak_t> ConnectionManager::GetParents(GameObject *child)
{
	auto list = vector<p_GameObjectWeak_t>();

	if (m_Parents.find(child->Id) != m_Parents.end())
	{
		for (auto pair : m_Parents[child->Id])
			list.push_back(pair.second);
	}

	return list;
}

vector<p_GameObjectWeak_t> ConnectionManager::GetAdditionals(GameObject *object)
{
	auto list = vector<p_GameObjectWeak_t>();

	for (auto index : m_Additionals)
	{
		if (index.firstIndex == object->Id ||
			index.secondIndex == object->Id)
		{
			if (index.firstIndex == object->Id)
				list.push_back(index.GetSecondPtr());
			else
				list.push_back(index.GetFirstPtr());
		}
	}

	return list;
}

vector<p_GameObjectWeak_t> ConnectionManager::GetIndepentent(GameObject *object)
{
	auto list = vector<p_GameObjectWeak_t>();

	for (auto index : m_Independent)
	{
		if (index.firstIndex == object->Id ||
			index.secondIndex == object->Id)
		{
			if (index.firstIndex == object->Id)
				list.push_back(index.GetSecondPtr());
			else
				list.push_back(index.GetFirstPtr());
		}
	}

	return list;
}

set<Connection, ConnectionOrdering> ConnectionManager::GetAllLinks(GameObject *object)
{
	auto list = set<Connection, ConnectionOrdering>();

	auto children = GetChildren(object);
	auto parents = GetParents(object);
	auto additionals = GetAdditionals(object);
	auto indepentent = GetIndepentent(object);

	for (auto ptr : children)
		list.insert({ConnectionTypes::Child, ptr});

	for (auto ptr : parents)
		list.insert({ConnectionTypes::Parent, ptr});

	for (auto ptr : additionals)
		list.insert({ConnectionTypes::Additional, ptr});

	for (auto ptr : indepentent)
		list.insert({ConnectionTypes::Independent, ptr});

	return list;
}

void ConnectionManager::RemoveLinks(GameObject *object)
{
	// TODO: implement
}

ConnectionTypes ConnectionManager::GetRelationship(GameObject *object, GameObject *other)
{
	if (m_Independent.find(Index(object->Id, other->Id)) != m_Independent.end())
		return ConnectionTypes::Independent;

	if (m_Additionals.find(Index(object->Id, other->Id)) != m_Additionals.end())
		return ConnectionTypes::Additional;

	if (m_Children.find(object->Id) != m_Children.end() &&
		m_Children[object->Id].find(other->Id) != m_Children[object->Id].end())
		return ConnectionTypes::Child;

	if (m_Children.find(other->Id) != m_Children.end() &&
		m_Children[other->Id].find(object->Id) != m_Children[other->Id].end())
		return ConnectionTypes::Parent;

	return ConnectionTypes::Unknown;
}
