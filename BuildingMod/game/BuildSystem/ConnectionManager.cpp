#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
	m_Additionals = set<Index>();
	m_Independent = set<Index>();

	m_Children = map<int, map<int, p_GameObjectWeak_t>>();
	m_Parents = map<int, map<int, p_GameObjectWeak_t>>();
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
	auto index = Index(object->Id, other->Id);

	// Check for duplicates
	if (m_Independent.find(index) != m_Independent.end())
		return false;

	m_Independent.insert(index);

	return true;
}

bool ConnectionManager::AddLinkAdditional(GameObject *object, GameObject *other)
{
	auto index = Index(object->Id, other->Id);

	// Check for duplicates
	if (m_Additionals.find(index) != m_Additionals.end())
		return false;

	m_Additionals.insert(index);

	return true;
}

set<p_GameObjectWeak_t> ConnectionManager::GetChildren(GameObject *parent)
{
	auto list = set<p_GameObjectWeak_t>();

	if (m_Children.find(parent->Id) != m_Children.end())
	{
		for (auto pair : m_Children[parent->Id])
			list.insert(pair.second);
	}

	return list;
}

set<p_GameObjectWeak_t> ConnectionManager::GetParents(GameObject *child)
{
	auto list = set<p_GameObjectWeak_t>();

	if (m_Parents.find(child->Id) != m_Parents.end())
	{
		for (auto pair : m_Parents[child->Id])
			list.insert(pair.second);
	}

	return list;
}

set<p_GameObjectWeak_t> ConnectionManager::GetAdditionals(GameObject *object)
{
	auto list = set<p_GameObjectWeak_t>();

	for (auto index : m_Additionals)
	{
		if (index.firstIndex == object->Id ||
			index.secondIndex == object->Id)
		{
			if (index.firstIndex == object->Id)
				list.insert(index.GetSecondPtr());
			else
				list.insert(index.GetFirstPtr());
		}
	}

	return list;
}

set<p_GameObjectWeak_t> ConnectionManager::GetIndepentent(GameObject *object)
{
	auto list = set<p_GameObjectWeak_t>();

	for (auto index : m_Independent)
	{
		if (index.firstIndex == object->Id ||
			index.secondIndex == object->Id)
		{
			if (index.firstIndex == object->Id)
				list.insert(index.GetSecondPtr());
			else
				list.insert(index.GetFirstPtr());
		}
	}

	return list;
}

set<Connection> ConnectionManager::GetAllLinks(GameObject *object)
{
	auto list = set<Connection>();

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
