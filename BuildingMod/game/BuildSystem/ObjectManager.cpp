#include "ObjectManager.h"

ObjectManager& ObjectManager::Instance()
{
	static ObjectManager manager;

	return manager;
}

void ObjectManager::Add(GameObject* object)
{
	if (Has(object->Id))
		return;

	m_Objects.insert(pair<int, p_GameObject_t>(
		object->Id, boost::make_shared<GameObject*>(object)
	));
}

void ObjectManager::Remove(GameObject* object)
{
}

bool ObjectManager::Has(int id)
{
	return m_Objects.find(id) != m_Objects.end();
}

bool ObjectManager::HasEdict(edict_t* edict)
{
	return m_ObjectsEdictIndex.find(ENTINDEX(edict)) != m_ObjectsEdictIndex.end();
}

void ObjectManager::Clear()
{
	auto it = m_Objects.begin();

	while (it != m_Objects.end())
	{
		it->second.reset();

		it = m_Objects.erase(it);
	}	
}

GameObject* ObjectManager::Get(int id)
{
	return nullptr;
}

p_GameObjectWeak_t ObjectManager::GetPtr(int id)
{
	return p_GameObjectWeak_t();
}

p_GameObjectWeak_t ObjectManager::GetPtrByEdict(edict_t* edict)
{
	if (!HasEdict(edict))
		return p_GameObjectWeak_t();

	return m_ObjectsEdictIndex.at(ENTINDEX(edict));
}

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
}
