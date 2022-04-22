#if !defined(_BUILDING_GAMEOBJECT_H_)
#define _BUILDING_GAMEOBJECT_H_

#include <pch.h>
#include "Link.h"
#include <interfaces/ObservableTransform.h>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	const int Id;

	void AddLink(int followPointId, Link link);
	void RemoveLink(int objectId);

	ObservableTransform* GetTransform();

	std::vector<std::pair<int, Link>> GetLinks();

protected:
	std::map<int, std::vector<Link>> m_links;

private:
	std::unique_ptr<ObservableTransform> m_transform;
};

#endif // _BUILDING_GAMEOBJECT_H_
