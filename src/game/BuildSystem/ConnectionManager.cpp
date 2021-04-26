#include "ConnectionManager.h"
#include <game/BuildSystem/Components/IStabilityComponent.h>

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

bool ConnectionManager::AddLinkParentChild(p_GameObject_t parent, p_GameObject_t child)
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

	auto res = res1.second && res2.second;

	return res;
}

bool ConnectionManager::AddLinkIndependent(p_GameObject_t object, p_GameObject_t other)
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

bool ConnectionManager::AddLinkAdditional(p_GameObject_t object, p_GameObject_t other)
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

map<int, p_GameObjectWeak_t> ConnectionManager::GetChildren(p_GameObject_t parent)
{
	auto list = map<int, p_GameObjectWeak_t>();

	if (m_Children.find(parent->Id) != m_Children.end())
	{
		for (auto pair : m_Children[parent->Id])
		{
			// Check for valid ptr
			if (pair.second.expired())
				continue;

			list.insert({pair.second.lock()->Id, pair.second});
		}
	}

	return list;
}

map<int, p_GameObjectWeak_t> ConnectionManager::GetParents(p_GameObject_t child)
{
	auto list = map<int, p_GameObjectWeak_t>();

	if (m_Parents.find(child->Id) != m_Parents.end())
	{
		for (auto pair : m_Parents[child->Id])
		{
			// Check for valid ptr
			if (pair.second.expired())
				continue;

			list.insert({pair.second.lock()->Id, pair.second});
		}
	}

	return list;
}

map<int, p_GameObjectWeak_t> ConnectionManager::GetAdditionals(p_GameObject_t object)
{
	auto list = map<int, p_GameObjectWeak_t>();

	for (auto index : m_Additionals)
	{
		if (!index.IsValid())
			continue;

		if (index.firstIndex == object->Id ||
			index.secondIndex == object->Id)
		{
			if (index.firstIndex == object->Id)
				list.insert({index.secondIndex, index.GetSecondPtr()});
			else
				list.insert({index.firstIndex, index.GetFirstPtr()});
		}
	}

	return list;
}

map<int, p_GameObjectWeak_t> ConnectionManager::GetIndepentent(p_GameObject_t object)
{
	auto list = map<int, p_GameObjectWeak_t>();

	for (auto index : m_Independent)
	{
		if (!index.IsValid())
			continue;

		if (index.firstIndex == object->Id ||
			index.secondIndex == object->Id)
		{
			if (index.firstIndex == object->Id)
				list.insert({index.secondIndex, index.GetSecondPtr()});
			else
				list.insert({index.firstIndex, index.GetFirstPtr()});
		}
	}

	return list;
}

set<Connection, ConnectionOrdering> ConnectionManager::GetAllLinks(p_GameObject_t object)
{
	auto list = set<Connection, ConnectionOrdering>();

	auto children = GetChildren(object);
	auto parents = GetParents(object);
	auto additionals = GetAdditionals(object);
	auto indepentent = GetIndepentent(object);

	for (auto [key, value] : children)
		list.insert({ConnectionTypes::Child, value});

	for (auto [key, value] : parents)
		list.insert({ConnectionTypes::Parent, value});

	for (auto [key, value] : additionals)
		list.insert({ConnectionTypes::Additional, value});

	for (auto [key, value] : indepentent)
		list.insert({ConnectionTypes::Independent, value});

	return list;
}

void ConnectionManager::RemoveLinks(int id)
{
	vector<p_GameObjectWeak_t> recalculationRequests;
	p_GameObjectWeak_t ptr;

	auto it_ind = m_Independent.begin();

	while (it_ind != m_Independent.end())
	{
		auto index = *it_ind;

		if (index.firstIndex == id || index.secondIndex == id)
		{
			it_ind = m_Independent.erase(it_ind);
			ptr = index.firstIndex == id ? index.GetSecondPtr() : index.GetFirstPtr();

			recalculationRequests.push_back(ptr);

			continue;
		}

		++it_ind;
	}

	auto it_add = m_Additionals.begin();

	while (it_add != m_Additionals.end())
	{
		auto index = *it_add;

		if (index.firstIndex == id || index.secondIndex == id)
		{
			it_add = m_Additionals.erase(it_add);
			ptr = index.firstIndex == id ? index.GetSecondPtr() : index.GetFirstPtr();

			auto size = m_Additionals.size();

			// Recalculate stability for second object
			// SendRecalculationRequest(ptr);

			recalculationRequests.push_back(ptr);

			// If recalculation request removed all links, current iterator
			// would be invalid, so, we need to break the cycle

			// if (size != m_Additionals.size())
			// 	it_add = m_Additionals.begin();

			continue;
		}

		++it_add;
	}

	auto it_child = m_Children.begin();

	while (it_child != m_Children.end())
	{
		auto pair = *it_child;

		if (pair.first == id)
		{
			it_child = m_Children.erase(it_child);

			auto size = m_Children.size();

			// Recalculate stability of children
			for (auto [key, value] : pair.second)
				recalculationRequests.push_back(value);
			// SendRecalculationRequest(value);

			if (size != m_Children.size())
				it_child = m_Children.begin();

			continue;
		}

		++it_child;
	}

	auto it_par = m_Parents.begin();

	while (it_par != m_Parents.end())
	{
		auto pair = *it_par;

		if (pair.first == id)
		{
			it_par = m_Parents.erase(it_par);

			for (auto [key, value] : pair.second)
				recalculationRequests.push_back(value);
			// SendRecalculationRequest(value);

			continue;
		}

		++it_par;
	}

	// ne rabotaet (9
	for (auto ptr : recalculationRequests)
	{
		SendRecalculationRequest(ptr);
	}
}

ConnectionTypes ConnectionManager::GetRelationship(p_GameObject_t object, p_GameObject_t other)
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

void ConnectionManager::SendRecalculationRequest(p_GameObjectWeak_t ptr)
{
	auto object = ptr.lock();

	if (object == nullptr)
		return;

	auto stability = object->GetComponent<IStabilityComponent>();

	if (stability == nullptr)
		return;

	stability->StartCalculation();
}
