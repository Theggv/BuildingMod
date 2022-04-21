#if !defined(_MANAGER_OBJECTMANAGER_)
#define _MANAGER_OBJECTMANAGER_

#include <pch.h>
#include <math/math_include.h>

class GameObject;

class ObjectManager
{
public:
    static ObjectManager &Instance();

    void Add(std::shared_ptr<GameObject *> object);
    void Remove(std::shared_ptr<GameObject *> object);

    bool Has(int id);
    bool HasEdict(edict_t *edict);

    void Clear();
    std::shared_ptr<GameObject *> Get(int id);
    std::weak_ptr<GameObject *> GetPtr(int id);

    std::weak_ptr<GameObject *> GetPtrByEdict(edict_t *edict);

    static unsigned long CalculateWorldPosition(float x, float y);
    void SetMapIndex(GameObject *object);

    aabb2 GetAreaByIndex(unsigned long index);
    std::vector<std::weak_ptr<GameObject *>> GetObjectsInArea(vec3 point, int range = 2);

private:
    // Map of pointers to objects by object index
    std::map<int, std::shared_ptr<GameObject *>> m_Objects;

    // Array of pointers to objects by position on map
    // Maximum map size is 8128x8128. It means we can split it by 128x128 zones.
    std::map<int, std::weak_ptr<GameObject *>> m_ObjectsMapIndex[64 * 64];

    // Map of pointers to objects by edict index
    // NOT IMPLEMENTED !
    std::map<int, std::weak_ptr<GameObject *>> m_ObjectsEdictIndex;

    ObjectManager();
    ~ObjectManager();

    ObjectManager(ObjectManager const &) = delete;
    ObjectManager &operator=(ObjectManager const &) = delete;
};

#endif // _MANAGER_OBJECTMANAGER_
