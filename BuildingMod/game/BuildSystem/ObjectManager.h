#pragma once

#include <pch.h>

using namespace std;

typedef boost::shared_ptr<GameObject*> p_GameObject_t;
typedef boost::weak_ptr<GameObject*> p_GameObjectWeak_t;

class ObjectManager
{
public:
	static ObjectManager& Instance();

	void Add(GameObject* object);
	void Remove(GameObject* object);
	bool Has(int id);
	void Clear();
	GameObject* Get(int id);
	p_GameObjectWeak_t GetPtr(int id);

private:
	// Map of pointers to objects by object index
	map<int, p_GameObject_t> m_Objects;

	// Array of pointers to objects by position on map
	// Maximum map size is 8128x8128. It means we can split it by 128x128 zones.
	set<p_GameObjectWeak_t> m_ObjectsMapIndex[64 * 64];

	// Map of pointers to objects by edict index
	map<int, p_GameObjectWeak_t> m_ObjectsEdictIndex;


	ObjectManager();
	~ObjectManager();

	ObjectManager(ObjectManager const&) = delete;
	ObjectManager& operator= (ObjectManager const&) = delete;
};
