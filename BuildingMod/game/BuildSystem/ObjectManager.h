#ifndef _BUILDSYSTEM_OBJECTMANAGER_
#define _BUILDSYSTEM_OBJECTMANAGER_

#include <pch.h>

using namespace std;

class GameObject;

typedef boost::shared_ptr<GameObject*> p_GameObject_t;
typedef boost::weak_ptr<GameObject*> p_GameObjectWeak_t;

class ObjectManager
{
public:
	static ObjectManager& Instance();

	void Add(GameObject* object);
	void Remove(GameObject* object);

	bool Has(int id);
	bool HasEdict(edict_t* edict);

	void Clear();
	GameObject* Get(int id);
	p_GameObjectWeak_t GetPtr(int id);

	p_GameObjectWeak_t GetPtrByEdict(edict_t* edict);

	static unsigned long CalculateWorldPosition(float x, float y);
private:
	// Map of pointers to objects by object index
	map<int, p_GameObject_t> m_Objects;

	// Array of pointers to objects by position on map
	// Maximum map size is 8128x8128. It means we can split it by 128x128 zones.
	//set<p_GameObjectWeak_t> m_ObjectsMapIndex[64 * 64];

	// Map of pointers to objects by edict index
	map<int, p_GameObjectWeak_t> m_ObjectsEdictIndex;


	ObjectManager();
	~ObjectManager();

	ObjectManager(ObjectManager const&) = delete;
	ObjectManager& operator= (ObjectManager const&) = delete;
};

#endif // !_BUILDSYSTEM_OBJECTMANAGER_