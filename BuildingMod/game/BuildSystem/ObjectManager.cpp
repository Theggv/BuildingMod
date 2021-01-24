#include "ObjectManager.h"

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

void ObjectManager::Add(GameObject *object)
{
	if (Has(object->Id))
		return;

	m_Objects.insert(pair<int, p_GameObject_t>(
		object->Id, boost::make_shared<GameObject *>(object)));

	// Start object
	object->Start();
}

void ObjectManager::Remove(GameObject *object)
{
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

GameObject *ObjectManager::Get(int id)
{
	if (!Has(id))
		return nullptr;

	return *m_Objects.at(id);
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

	return m_ObjectsEdictIndex.at(ENTINDEX(edict));
}

unsigned long ObjectManager::CalculateWorldPosition(float x, float y)
{
	// [-4096; 4096] -> [0; 8192]

	auto _x = (unsigned int)(x + 4096) / 128;
	auto _y = (unsigned int)(y + 4096) / 128;

	return _x + _y * 64;

	// old impl

	// [-4096; 4096] -> [0; 8192]

	// auto _x = (unsigned int)(x + 4096);
	// auto _y = (unsigned int)(y + 4096);

	// unsigned long position = 0;

	// unsigned int flags = 0;
	// unsigned int gridSize = 4096;

	// for (int i = 0; i < 7; ++i)
	// {
	// 	flags = ((_x >= gridSize) << 1) | (_y >= gridSize);

	// 	position |= flags << (i * 2);

	// 	if (_x >= gridSize)
	// 		_x -= gridSize;

	// 	if (_y >= gridSize)
	// 		_y -= gridSize;

	// 	gridSize /= 2;
	// }

	// return position;
}

void ObjectManager::SetMapIndex(GameObject *object)
{
	auto id = object->Id;

	auto index = object->GetWorldPositionFlags();

	m_ObjectsMapIndex[index]
		.insert(std::pair(id, p_GameObjectWeak_t(m_Objects.at(id))));
}

aabb2 ObjectManager::GetAreaByIndex(unsigned long index)
{
	auto _x = (index % 64) * 128 - 4096.0;
	auto _y = (index / 64) * 128 - 4096.0;

	return aabb2(vec2(_x, _y), vec2(_x + 128, _y + 128));
}

vector<p_GameObjectWeak_t> ObjectManager::GetObjectsInArea(vec3& point, int range)
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
