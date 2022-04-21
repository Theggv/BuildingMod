#if !defined(_INTERFACES_GAMEOBJECT_)
#define _INTERFACES_GAMEOBJECT_

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

    ObservableTransform *GetTransform();

    std::vector<std::pair<int, Link>> GetLinks();

protected:
    std::map<int, std::vector<Link>> m_links;

private:
    std::unique_ptr<ObservableTransform> m_transform;
};

#endif // _INTERFACES_GAMEOBJECT_
