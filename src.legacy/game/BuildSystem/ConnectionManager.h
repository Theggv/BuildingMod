#ifndef _BUILDSYSTEM_CONNECTIONMANAGER_
#define _BUILDSYSTEM_CONNECTIONMANAGER_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/StabilityComponent/ConnectionTypes.h>

using namespace std;

class ConnectionManager
{
public:
	static ConnectionManager &Instance();

	bool AddLinkParentChild(GameObject *parent, GameObject *child);
	bool AddLinkIndependent(GameObject *object, GameObject *other);
	bool AddLinkAdditional(GameObject *object, GameObject *other);

	map<int, p_GameObjectWeak_t> GetChildren(GameObject *parent);
	map<int, p_GameObjectWeak_t> GetParents(GameObject *child);
	map<int, p_GameObjectWeak_t> GetAdditionals(GameObject *object);
	map<int, p_GameObjectWeak_t> GetIndepentent(GameObject *object);

	ConnectionTypes GetRelationship(GameObject *object, GameObject *other);

	set<Connection, ConnectionOrdering> GetAllLinks(GameObject *object);

	void RemoveLinks(GameObject *object);

private:
	struct Index
	{
	public:
		int firstIndex;
		int secondIndex;

		Index(int first, int second) : firstIndex(first), secondIndex(second)
		{
			firstPtr = ObjectManager::Instance().GetPtr(firstIndex);
			secondPtr = ObjectManager::Instance().GetPtr(secondIndex);
		}

		Index() : Index(0, 0) {}

		inline p_GameObjectWeak_t GetFirstPtr()
		{
			return firstPtr;
		}

		inline p_GameObjectWeak_t GetSecondPtr()
		{
			return secondPtr;
		}

		inline bool IsValid()
		{
			return !firstPtr.expired() && !secondPtr.expired();
		}

	private:
		p_GameObjectWeak_t firstPtr;
		p_GameObjectWeak_t secondPtr;
	};

	struct IndexOrdering
	{
		// impl of < operator
		bool operator()(Index const &lhs, Index const &rhs) const
		{
			if (min(lhs.firstIndex, lhs.secondIndex) == min(rhs.firstIndex, rhs.secondIndex))
				return max(lhs.firstIndex, lhs.secondIndex) < max(rhs.firstIndex, rhs.secondIndex);

			return min(lhs.firstIndex, lhs.secondIndex) < min(rhs.firstIndex, rhs.secondIndex);
		}
	};

	set<Index, IndexOrdering> m_Independent;
	set<Index, IndexOrdering> m_Additionals;
	map<int, map<int, p_GameObjectWeak_t>> m_Parents;
	map<int, map<int, p_GameObjectWeak_t>> m_Children;

	ConnectionManager();
	~ConnectionManager();

	ConnectionManager(ConnectionManager const &) = delete;
	ConnectionManager &operator=(ConnectionManager const &) = delete;
};

#endif // !_BUILDSYSTEM_CONNECTIONMANAGER_