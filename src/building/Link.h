#if !defined(_INTERFACES_LINK_)
#define _INTERFACES_LINK_

#include <pch.h>

class GameObject;

enum class LinkType
{
    PARENT,
    CHILD,
    SUPPORT,
    INDEPENDANT,
};

struct Link
{
    LinkType type;
    std::weak_ptr<GameObject> object;
};

#endif // _INTERFACES_LINK_
