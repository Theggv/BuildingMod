#ifndef _BUILDSYSTEM_OBJECTMANAGER_
#define _BUILDSYSTEM_OBJECTMANAGER_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>

#include <game/Geometry.h>

typedef shared_ptr<GameObject *> p_GameObject_t;
typedef weak_ptr<GameObject *> p_GameObjectWeak_t;

using namespace std;

class ObjectManager
{
public:
	static ObjectManager &Instance();

	void Add(GameObject *object);
	void Remove(GameObject *object);

	bool Has(int id);
	bool HasEdict(edict_t *edict);

	void Clear();
	GameObject *Get(int id);
	p_GameObjectWeak_t GetPtr(int id);

	p_GameObjectWeak_t GetPtrByEdict(edict_t *edict);

	static unsigned long CalculateWorldPosition(float x, float y);
	void SetMapIndex(GameObject *object);

	aabb2 GetAreaByIndex(unsigned long index);
	vector<p_GameObjectWeak_t> GetObjectsInArea(vec3 point, int range = 2);

private:
	// Map of pointers to objects by object index
	map<int, p_GameObject_t> m_Objects;

	// Array of pointers to objects by position on map
	// Maximum map size is 8128x8128. It means we can split it by 128x128 zones.
	map<int, p_GameObjectWeak_t> m_ObjectsMapIndex[64 * 64];

	// Map of pointers to objects by edict index
	// NOT IMPLEMENTED !
	map<int, p_GameObjectWeak_t> m_ObjectsEdictIndex;

	ObjectManager();
	~ObjectManager();

	ObjectManager(ObjectManager const &) = delete;
	ObjectManager &operator=(ObjectManager const &) = delete;
};

#endif // !_BUILDSYSTEM_OBJECTMANAGER_