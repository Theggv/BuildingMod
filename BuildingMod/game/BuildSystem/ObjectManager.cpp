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

	// Start object
	object->Start();
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

unsigned long ObjectManager::CalculateWorldPosition(float x, float y)
{
	auto _x = (unsigned int)(x + 4096);
	auto _y = (unsigned int)(y + 4096);

	unsigned long position = 0;

	unsigned int flags = 0;
	unsigned int gridSize = 4096;

	for (int i = 0; i < 7; ++i)
	{
		flags = ((_x >= gridSize) << 1) | (_y >= gridSize);

		position |= flags << (i * 2);

		if (_x >= gridSize)
			_x -= gridSize;

		if (_y >= gridSize)
			_y -= gridSize;

		gridSize /= 2;
	}

	return position;
}

ObjectManager::ObjectManager()
{
	m_Objects = map<int, p_GameObject_t>();
	m_ObjectsEdictIndex = map<int, p_GameObjectWeak_t>();
}

ObjectManager::~ObjectManager()
{

}
