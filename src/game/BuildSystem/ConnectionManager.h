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

	bool AddLinkParentChild(p_GameObject_t parent, p_GameObject_t child);
	bool AddLinkIndependent(p_GameObject_t object, p_GameObject_t other);
	bool AddLinkAdditional(p_GameObject_t object, p_GameObject_t other);

	map<int, p_GameObjectWeak_t> GetChildren(p_GameObject_t parent);
	map<int, p_GameObjectWeak_t> GetParents(p_GameObject_t child);
	map<int, p_GameObjectWeak_t> GetAdditionals(p_GameObject_t object);
	map<int, p_GameObjectWeak_t> GetIndepentent(p_GameObject_t object);

	ConnectionTypes GetRelationship(p_GameObject_t object, p_GameObject_t other);

	set<Connection, ConnectionOrdering> GetAllLinks(p_GameObject_t object);

	void RemoveLinks(p_GameObject_t object);

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

	void SendRecalculationRequest(p_GameObjectWeak_t ptr);
};

#endif // !_BUILDSYSTEM_CONNECTIONMANAGER_