#include "ObjectManager.h"
#include <Utility/EdictFlags.h>

ObjectManager::ObjectManager()
{
	m_Objects = map<int, p_GameObject_t>();
	m_ObjectsEdictIndex = map<int, p_GameObjectWeak_t>();

	for (size_t i = 0; i < 64 * 64; i++)
	{
		m_ObjectsMapIndex[i] = map<int, p_GameObjectWeak_t>();
	}
}

ObjectManager::~ObjectManager()
{
}

ObjectManager &ObjectManager::Instance()
{
	static ObjectManager manager;

	return manager;
}

p_GameObject_t ObjectManager::Add(p_GameObject_t object)
{
	auto id = object->Id;

	if (Has(id))
		return Get(id);

	m_Objects.insert(
		{id,
		 move(object)});

	return Get(id);
}

void ObjectManager::Remove(p_GameObject_t object)
{
	// Prevent double delete if clean was started
	if (m_IsCleanStarted)
		return;

	auto id = object->Id;

	if (!Has(id))
		return;

	auto index = object->GetWorldPositionFlags();

	m_Objects.erase(id);
	m_ObjectsMapIndex[index].erase(id);
}

bool ObjectManager::Has(int id)
{
	return m_Objects.find(id) != m_Objects.end();
}

bool ObjectManager::HasEdict(edict_t *edict)
{
	return Has(EdictFlags::GetFlags(edict));
}

void ObjectManager::Clear()
{
	m_IsCleanStarted = true;

	for (size_t i = 0; i < 64 * 64; i++)
	{
		m_ObjectsMapIndex[i].clear();
	}

	m_ObjectsEdictIndex.clear();

	auto it = m_Objects.begin();

	while (it != m_Objects.end())
	{
		auto size = m_Objects.size();

		it = m_Objects.erase(it);

		// ptr ruined smh
		if (size - 1 != m_Objects.size())
			it = m_Objects.begin();
	}

	m_IsCleanStarted = false;
}

p_GameObject_t ObjectManager::Get(int id)
{
	if (!Has(id))
		return nullptr;

	return m_Objects.at(id);
}

p_GameObjectWeak_t ObjectManager::GetPtr(int id)
{
	if (!Has(id))
		return p_GameObjectWeak_t();

	return p_GameObjectWeak_t(m_Objects.at(id));
}

p_GameObjectWeak_t ObjectManager::GetPtrByEdict(edict_t *edict)
{
	if (!HasEdict(edict))
		return p_GameObjectWeak_t();

	auto id = EdictFlags::GetFlags(edict);

	return GetPtr(id);
}

unsigned long ObjectManager::CalculateWorldPosition(float x, float y)
{
	auto _x = (unsigned int)(x + 4096) / 128;
	auto _y = (unsigned int)(y + 4096) / 128;

	return _x + _y * 64;
}

void ObjectManager::SetMapIndex(p_GameObject_t object)
{
	auto id = object->Id;

	auto index = object->GetWorldPositionFlags();

	m_ObjectsMapIndex[index]
		.insert(
			{id,
			 p_GameObjectWeak_t(object)});
}

aabb2 ObjectManager::GetAreaByIndex(unsigned long index)
{
	auto _x = (index % 64) * 128 - 4096.0;
	auto _y = (index / 64) * 128 - 4096.0;

	return aabb2(vec2(_x, _y), vec2(_x + 128, _y + 128));
}

vector<p_GameObjectWeak_t> ObjectManager::GetObjectsInArea(vec3 point, int range)
{
	auto fromIndex = CalculateWorldPosition(point.x, point.y);

	vector<p_GameObjectWeak_t> objects;

	auto x_from = fromIndex % 64;
	auto y_from = fromIndex / 64;

	for (size_t i = max(x_from - range, 0); i < min(x_from + range, 64); i++)
	{
		for (size_t j = max(y_from - range, 0); j < min(y_from + range, 64); j++)
		{
			auto index = i + j * 64;
			auto area = GetAreaByIndex(index);

			for (auto pair : m_ObjectsMapIndex[index])
			{
				objects.push_back(pair.second);
			}
		}
	}

	return objects;
}
