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

	set<p_GameObjectWeak_t> GetChildren(GameObject *parent);
	set<p_GameObjectWeak_t> GetParents(GameObject *child);
	set<p_GameObjectWeak_t> GetAdditionals(GameObject *object);
	set<p_GameObjectWeak_t> GetIndepentent(GameObject *object);

	set<Connection> GetAllLinks(GameObject *object);

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

		inline p_GameObjectWeak_t GetFirstPtr()
		{
			return firstPtr;
		}

		inline p_GameObjectWeak_t GetSecondPtr()
		{
			return secondPtr;
		}

		inline bool operator==(const Index &rhs)
		{
			return (firstIndex == rhs.firstIndex &&
					secondIndex == rhs.secondIndex) ||
				   (firstIndex == rhs.secondIndex &&
					secondIndex == rhs.firstIndex);
		}

		inline bool operator!=(const Index &rhs)
		{
			return !((firstIndex == rhs.firstIndex &&
					  secondIndex == rhs.secondIndex) ||
					 (firstIndex == rhs.secondIndex &&
					  secondIndex == rhs.firstIndex));
		}

		friend bool operator<(const Index &lhs, const Index &rhs)
		{
			return min(lhs.firstIndex, lhs.secondIndex) < min(rhs.firstIndex, rhs.secondIndex);
		}

		friend bool operator>(const Index &lhs, const Index &rhs)
		{
			return max(lhs.firstIndex, lhs.secondIndex) > max(rhs.firstIndex, rhs.secondIndex);
		}

	private:
		p_GameObjectWeak_t firstPtr;
		p_GameObjectWeak_t secondPtr;
	};

	set<Index> m_Independent;
	set<Index> m_Additionals;
	map<int, map<int, p_GameObjectWeak_t>> m_Parents;
	map<int, map<int, p_GameObjectWeak_t>> m_Children;

	ConnectionManager();
	~ConnectionManager();

	ConnectionManager(ConnectionManager const &) = delete;
	ConnectionManager &operator=(ConnectionManager const &) = delete;
};

#endif // !_BUILDSYSTEM_CONNECTIONMANAGER_