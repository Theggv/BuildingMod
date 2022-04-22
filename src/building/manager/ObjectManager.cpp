
#include "ObjectManager.h"
#include <building/GameObject.h>
#include <interfaces/EdictFlags.h>

ObjectManager::ObjectManager()
{
    m_Objects = std::map<int, std::shared_ptr<GameObject *>>();
    m_ObjectsEdictIndex = std::map<int, std::weak_ptr<GameObject *>>();

    for (size_t i = 0; i < 64 * 64; i++)
    {
        m_ObjectsMapIndex[i] = std::map<int, std::weak_ptr<GameObject *>>();
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

void ObjectManager::Add(std::shared_ptr<GameObject *> ptr)
{
    if (!ptr)
        return;

    auto object = *ptr;

    if (Has(object->Id))
        return;

    m_Objects.insert(std::pair<int, std::shared_ptr<GameObject *>>(
        object->Id, ptr));

    // OnStart object
    // object->OnStart();
}

void ObjectManager::Remove(std::shared_ptr<GameObject *> ptr)
{
    if (!ptr)
        return;

    auto object = *ptr;
    auto id = object->Id;

    if (!Has(id))
        return;

    //auto index = object->GetWorldPositionFlags();

    m_Objects.erase(id);
    /*m_ObjectsMapIndex[index].erase(id);*/
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
    for (size_t i = 0; i < 64 * 64; i++)
    {
        m_ObjectsMapIndex[i].clear();
    }

    m_ObjectsEdictIndex.clear();

    auto it = m_Objects.begin();

    while (it != m_Objects.end())
    {
        it->second.reset();

        it = m_Objects.erase(it);
    }
}

std::shared_ptr<GameObject *> ObjectManager::Get(int id)
{
    if (!Has(id))
        return nullptr;

    return m_Objects.at(id);
}

std::weak_ptr<GameObject *> ObjectManager::GetPtr(int id)
{
    if (!Has(id))
        return std::weak_ptr<GameObject *>();

    return std::weak_ptr<GameObject *>(m_Objects.at(id));
}

std::weak_ptr<GameObject *> ObjectManager::GetPtrByEdict(edict_t *edict)
{
    if (!HasEdict(edict))
        return std::weak_ptr<GameObject *>();

    auto id = EdictFlags::GetFlags(edict);

    return GetPtr(id);
}

unsigned long ObjectManager::CalculateWorldPosition(float x, float y)
{
    auto _x = (unsigned int)(x + 4096) / 128;
    auto _y = (unsigned int)(y + 4096) / 128;

    return _x + _y * 64;
}

void ObjectManager::SetMapIndex(GameObject *object)
{
    auto id = object->Id;

    //auto index = object->GetWorldPositionFlags();

  /*  m_ObjectsMapIndex[index]
        .insert(std::pair(id, std::weak_ptr<GameObject *>(m_Objects.at(id))));*/
}

aabb2 ObjectManager::GetAreaByIndex(unsigned long index)
{
    auto _x = (index % 64) * 128 - 4096.0;
    auto _y = (index / 64) * 128 - 4096.0;

    return aabb2(vec2(_x, _y), vec2(_x + 128, _y + 128));
}

std::vector<std::weak_ptr<GameObject *>> ObjectManager::GetObjectsInArea(vec3 point, int range)
{
    auto fromIndex = CalculateWorldPosition(point.x, point.y);

    std::vector<std::weak_ptr<GameObject *>> objects;

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
